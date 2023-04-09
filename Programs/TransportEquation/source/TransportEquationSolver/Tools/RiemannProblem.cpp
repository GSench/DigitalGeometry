//
// Created by grigoriy.senchenok on 09.12.2022.
//

#include "RiemannProblem.h"
#include "../../math/MathUtils.h"

const int SL = 0;
const int SR = 1;
const int GL = 2;
const int GR = 3;

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
    if(QL.isDiscontinuous(eps))
        if(QR.isSolid(eps))
            return SL;
        else
            return GR;
    else
        if(QL.isSolid(eps))
            return SR;
        else
            return GL;
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

GSFlow RP(const GSQuantity& QL, const GSQuantity& QR, double dt){
    GSFlow FL(QL);
    GSFlow FR(QR);
    pair<double,double> slr = RPWaves(QL.velocity(), QL.velocity(), QL.soundSpeed(), QR.soundSpeed());
    double sl = slr.first;
    double sr = slr.second;
    GSFlow FDiscontinuity = (sr*FL - sl*FR + sl * sr * toFlow(QR - QL)) / (sr - sl);
    return FDiscontinuity*dt;
}

GSFlow CRP(const GSQuantity& QL, const GSQuantity& QR, double dt, double dx, double eps){

    int config = defineConfig(QL, QR, eps);
    GSQuantity QLCalc = QL;
    GSQuantity QRCalc = QR;
    // Reconfiguring discontinuity right to left
    if(rightDiscontinuousCase(config)){
        QLCalc.inverse();
        QRCalc.inverse();
        swap(QLCalc, QRCalc);
    }

    // only SL, GL cases are considered
    double xs = (solidCase(config) ? QLCalc.volumeFraction() - 1 : QRCalc.volumeFraction()) * dx;
    double vs = QRCalc.getSolidVelocity();
    double t1 = -xs/vs;
    double tau1 = t1>=0 && t1<=dt ? t1/dt : 1.0;

    GSQuantity QL_avg = gasCase(config) ?
            QLCalc :
            (QLCalc + QRCalc) / (QLCalc.volumeFraction() + QRCalc.volumeFraction());


    double ul = QL_avg.velocity();
    double al = QL_avg.soundSpeed();
    double sl = CRPSWave(ul, al, vs);
    double t2 = -xs/sl;
    double tau2 = t2>=0 && t2<=dt ? t2/dt : 1.0;

    double rhoL = QL_avg.density();
    double pL = QL_avg.pressure();
    double El = QL_avg.energy();

    double uv = (ul-sl)/(vs-sl);
    GSQuantity QStar(
            Vector({
                1,
                uv*rhoL,
                uv*rhoL*vs,
                uv*(rhoL*El + (ul-vs)*(pL/(ul-sl) - rhoL*vs))
            }),
            QL_avg.getGamma(),
            0
    );
    GSFlow FStar = GSFlow(QL_avg) + sl * toFlow(QStar - QL_avg);

    GSFlow FBorder = solidCase(config) ?
            (toFlow(QL_avg)*(1.0-tau2) + FStar * (tau2 - tau1))*dt :
            (toFlow(QL_avg)*tau2 + FStar * (tau1 - tau2))*dt ;

    //GSFlow GL = (FStar - vs* toFlow(QStar))*(solidCase(config) ? tau1 : 1 - tau1) * dt;
    GSFlow GPlus = (FStar - vs* toFlow(QStar))*(solidCase(config) ? 1 - tau1 : tau1) * dt;

    GSFlow flow = FBorder + GPlus;

    if(rightDiscontinuousCase(config))
        flow.inverse();

    return flow;
}