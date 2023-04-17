//
// Created by grigoriy.senchenok on 09.12.2022.
//

#include "RiemannProblem.h"
#include "../Methods/Mesh.h"

const int SL = 0;
const int SR = 1;
const int GL = 2;
const int GR = 3;
const int GS = 4;
const int SG = 5;

pair<double, double> RPWaves(double ul, double ur, double al, double ar){
    return {
        /*sl=*/min(0., min(ul-al, avg<double>({ul,ur})-avg<double>({al,ar}))),
        /*sr=*/max(0., max(ar+ar, avg<double>({ul,ur})+avg<double>({al,ar})))
    };
}

double CRPSWave(double ul, double al, double vs){
    return /*sl=*/min(0., min(ul-al, vs-al));
}

int defineConfig(const GSQuantity& QL, const GSQuantity& QR, double eps){
    if(QL.isDiscontinuous(eps)) {
        if (QR.isSolid(eps))
            return SL;
        else if (QR.isGas(eps))
            return GR;
    } else if(QR.isDiscontinuous(eps)) {
        if (QL.isSolid(eps))
            return SR;
        else if (QL.isGas(eps))
            return GL;
    } else if(QL.isGas(eps) && QR.isSolid(eps))
        return GS;
    else if(QR.isGas(eps) && QL.isSolid(eps))
        return SG;
    return -1;
}

bool solidCase(int config){
    return config == SL || config == SR;
}

bool gasCase(int config){
    return config == GL || config == GR;
}

bool leftDiscontinuousCase(int config){
    return config == SL || config == GL;
}

bool rightDiscontinuousCase(int config){
    return config == SR || config == GR;
}

bool centerDiscontinuousCase(int config){
    return config == SG || config == GS;
}

GSFlow RP(const GSQuantity& QL, const GSQuantity& QR, double dt){
    GSFlow FL(QL);
    GSFlow FR(QR);
    pair<double,double> slr = RPWaves(QL.velocity(), QR.velocity(), QL.soundSpeed(), QR.soundSpeed());
    double sl = slr.first;
    double sr = slr.second;
    GSFlow FDiscontinuity = (sr*FL - sl*FR + sl * sr * toFlow(QR - QL)) / (sr - sl);
    return FDiscontinuity*dt;
}

GSFlow CRPnoPadding(const GSQuantity& QL, const GSQuantity& QR, double dt, double eps, int dirLR){
    GSQuantity QLCalc = QL;
    GSQuantity QRCalc = QR;
    if(QL.isSolid(eps)){
        QLCalc.inverse();
        QRCalc.inverse();
        swap(QLCalc, QRCalc);
        dirLR = inverseDirLR(dirLR);
    }

    double vs = QRCalc.getSolidVelocity();
    double ul = QLCalc.velocity();
    double al = QLCalc.soundSpeed();
    double sl = CRPSWave(ul, al, vs);


    double rhoL = QLCalc.density();
    double pL = QLCalc.pressure();
    double El = QLCalc.energy();

    double denominatorUV = ifZero(vs-sl, eps);
    double uv = ifZero(ul-sl, eps);
    uv/=denominatorUV;
    GSQuantity QStar(
            Vector({
                           1,
                           uv*rhoL,
                           uv*rhoL*vs,
                           uv*(rhoL*El + (ul-vs)*(pL/ifZero(ul-sl, eps) - rhoL*vs))
                   }),
            QLCalc.getGamma(),
            vs
    );
    GSFlow FStar = GSFlow(QLCalc) + sl * toFlow(QStar - QLCalc);

    GSFlow FBorder = vs > 0.0 ?
            (sl < 0.0 ?
                FStar : //    sl\|/vs
                GSFlow(QLCalc) //    |/sl/vs
            ) :
            zero(QRCalc); //    sl\vs\|
    FBorder *= dt;

    GSFlow flow = FBorder;

    GSFlow G = (FStar - vs* toFlow(QStar)) * dt;
    if(vs >= 0.0){
        if(dirLR == L)
            flow -= G;
    } else if(vs < 0.0) {
        if(dirLR == R)
            flow += G;
    }

    if(QL.isSolid(eps))
        flow.inverse();

    return flow;
}

GSFlow CRP(const GSQuantity& QL, const GSQuantity& QR, double dt, double dx, double eps, int dirLR){

    int config = defineConfig(QL, QR, eps);
    GSQuantity QLCalc = QL;
    GSQuantity QRCalc = QR;
    // Reconfiguring discontinuity right to left
    if(rightDiscontinuousCase(config)){
        QLCalc.inverse();
        QRCalc.inverse();
        swap(QLCalc, QRCalc);
        dirLR = inverseDirLR(dirLR);
    }

    // only SL, GL cases are considered
    double xs = (solidCase(config) ? QLCalc.volumeFraction() - 1 : QRCalc.volumeFraction()) * dx;
    double vs = QRCalc.getSolidVelocity();
    double t1 = -xs/ifZero(vs, eps);
    double tau1 = t1>=0 && t1<=dt ? t1/dt : 1.0;

    GSQuantity QL_avg = gasCase(config) ?
            QLCalc :
            (QLCalc + QRCalc) / (QLCalc.volumeFraction() + QRCalc.volumeFraction());


    double ul = QL_avg.velocity();
    double al = QL_avg.soundSpeed();
    double sl = CRPSWave(ul, al, vs);
    double t2 = -xs/ifZero(sl, eps);
    double tau2 = t2>=0 && t2<=dt ? t2/dt : 1.0;

    double rhoL = QL_avg.density();
    double pL = QL_avg.pressure();
    double El = QL_avg.energy();

    double denominatorUV = ifZero(vs-sl, eps);
    double uv = ifZero(ul-sl, eps);
    uv/=denominatorUV;
    GSQuantity QStar(
            Vector({
                1,
                uv*rhoL,
                uv*rhoL*vs,
                uv*(rhoL*El + (ul-vs)*(pL/ifZero(ul-sl, eps) - rhoL*vs))
            }),
            QL_avg.getGamma(),
            vs
    );
    GSFlow FStar = GSFlow(QL_avg) + sl * toFlow(QStar - QL_avg);

    GSFlow FBorder = solidCase(config) ?
            (GSFlow(QL_avg)*(1.0-tau2) + FStar * (tau2 - tau1))*dt :
            (GSFlow(QL_avg)*tau2 + FStar * (tau1 - tau2))*dt ;

    GSFlow flow = FBorder;

    if(t1 >= dt){
        GSFlow G = (FStar - vs* toFlow(QStar)) * dt;
        if(vs >= 0.0){
            if(dirLR == R)
                flow += G;
        } else if(vs < 0.0) {
            if(dirLR == L)
                flow -= G;
        }
    } else if(t1 >= 0.0) {
        GSFlow GMinus = (FStar - vs* toFlow(QStar))*t1;
        GSFlow GPlus = (FStar - vs* toFlow(QStar))*(dt-t1);
        if(vs >= 0.0){
            if(dirLR == R)
                flow += GMinus;
            else
                flow -= GPlus;
        } else {
            if(dirLR == R)
                flow += GPlus;
            else
                flow -= GMinus;
        }
    }

    if(rightDiscontinuousCase(config))
        flow.inverse();

    return flow;
}

GSFlow CRPMastering(const GSQuantity& QL, const GSQuantity& QR, double dt, double dx, double eps, int dirLR){

    int config = defineConfig(QL, QR, eps);
    GSQuantity QLCalc = QL;
    GSQuantity QRCalc = QR;
    // Reconfiguring discontinuity right to left
    if(rightDiscontinuousCase(config)){
        QLCalc.inverse();
        QRCalc.inverse();
        swap(QLCalc, QRCalc);
        dirLR = inverseDirLR(dirLR);
    }

    // only SL, GL cases are considered
    double xs = (solidCase(config) ? QLCalc.volumeFraction() - 1 : QRCalc.volumeFraction()) * dx;
    double vs = QRCalc.getSolidVelocity();
    double t2 = -xs/ifZero(vs, eps);
    double tau2 = t2>=0 && t2<=dt ? t2/dt : 0.0;

    GSQuantity QL_avg = gasCase(config) ?
                        QLCalc :
                        (QLCalc + QRCalc) / (QLCalc.volumeFraction() + QRCalc.volumeFraction());


    double ul = QL_avg.velocity();
    double al = QL_avg.soundSpeed();
    double sl = CRPSWave(ul, al, vs);
    double t1 = -xs/ifZero(sl, eps);
    double tau1 = t1>=0 && t1<=dt ? t1/dt : 0.0;

    double rhoL = QL_avg.density();
    double pL = QL_avg.pressure();
    double El = QL_avg.energy();

    double denominatorUV = ifZero(vs-sl, eps);
    double uv = ifZero(ul-sl, eps);
    uv/=denominatorUV;
    GSQuantity QStar(
            Vector({
                           1,
                           uv*rhoL,
                           uv*rhoL*vs,
                           uv*(rhoL*El + (ul-vs)*(pL/ifZero(ul-sl, eps) - rhoL*vs))
                   }),
            QL_avg.getGamma(),
            vs
    );
    GSFlow FStar = GSFlow(QL_avg) + sl * toFlow(QStar - QL_avg);

    GSFlow FBorder = (
            FStar * (tau2 - tau1) * (1.0 - 2 * H(-xs))
            + GSFlow(QL_avg)*(1.0-tau2+(2.0*tau2-1.0)* H(-xs))
            )*dt;

    GSFlow G = -1.0 * (FStar - vs* toFlow(QStar));
    GSFlow GMinus = G * (tau1 + (1.0-2.0*tau1)*H(-xs)) * dt;
    GSFlow GPlus = G * (1.0 - tau1 + (2.0*tau1 - 1.0)*H(-xs)) * dt;

    GSFlow flow = FBorder;
    if(solidCase(config)){
        GMinus = zero(QRCalc);
    }

    if(dirLR == R){
        flow -= GMinus;
    } else {
        flow += GPlus;
    }

    if(rightDiscontinuousCase(config))
        flow.inverse();

    return flow;
}