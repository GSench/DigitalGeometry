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

const string configTitles[] = {"SL", "SR", "GL", "GR", "GS", "SG"};

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

vector<GSFlow> RP(const GSQuantity& QL, const GSQuantity& QR, double dt){
    GSFlow FL(QL);
    GSFlow FR(QR);
    pair<double,double> slr = RPWaves(QL.velocity(), QR.velocity(), QL.soundSpeed(), QR.soundSpeed());
    double sl = slr.first;
    double sr = slr.second;
    GSFlow FDiscontinuity = (sr*FL - sl*FR + sl * sr * toFlow(QR - QL)) / (sr - sl);
    return {FDiscontinuity*dt, zero(QL), zero(QL)};
}

vector<GSFlow> CRPnoPadding(const GSQuantity& QL, const GSQuantity& QR, double dt, double dx, double eps, int dirLR){
    int config = defineConfig(QL, QR, eps);
    GSQuantity QLCalc = QL;
    GSQuantity QRCalc = QR;
    // Reconfiguring discontinuity right to left
    if(QL.isSolid(eps)){
        QLCalc.inverse();
        QRCalc.inverse();
        swap(QLCalc, QRCalc);
        dirLR = inverseDirLR(dirLR);
    }
    GSFlow FR = zero(QRCalc);

    // only SL, GL cases are considered
    double xs = 0;
    double vs = QRCalc.getSolidVelocity();

    GSQuantity QL_avg = QLCalc;
    GSFlow FL = GSFlow(QL_avg);

    double ul = QL_avg.velocity();
    double al = QL_avg.soundSpeed();
    double sl = CRPSWave(ul, al, vs);

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
    GSFlow FStar = FL + sl * toFlow(QStar - QL_avg);

    GSFlow FBorder = (vs <= 0.0 ? FR : (sl >=0 ? FL : FStar)) * dt;

    GSFlow flow = FBorder;

    double n = QL.isGas(eps) ? -1.0 : 1.0;
    GSFlow G = n * (FStar - vs* toFlow(QStar));

    GSFlow GMinus = vs >= 0 ? zero(QL_avg) : G*dt;
    GSFlow GPlus = vs < 0 ? zero(QRCalc) : G*dt;

    if(vs < 0.0){
        double t3 = (-dx - xs)/ifZero(vs, eps);
        double tau3 = t3>=0 && t3<=dt ? t3/dt : 1.0;
        GMinus *= tau3;
    } else {
        double t3 = (dx - xs)/ifZero(vs, eps);
        double tau3 = t3>=0 && t3<=dt ? t3/dt : 1.0;
        GPlus *= tau3;
    }

    if(solidCase(config)){
        GMinus *= 0.0;
    }

    if(QL.isSolid(eps)) {
        flow.inverse();
        GMinus.inverse();
        GPlus.inverse();
        swap(GMinus, GPlus);
    }

    return {flow, GMinus, GPlus};
}

vector<GSFlow> CRP(const GSQuantity& QL, const GSQuantity& QR, double dt, double dx, double eps, int dirLR, bool debugMode, Logger& logger){

    int config = defineConfig(QL, QR, eps);

    if(debugMode){
        logger.log("CRP");
        logger.log("QL", QL.toString());
        logger.log("QR", QR.toString());
        logger.log("config", configTitles[config]);
    }

    GSQuantity QLCalc = QL;
    GSQuantity QRCalc = QR;

    // Reconfiguring discontinuity right to left
    if(rightDiscontinuousCase(config)){
        QLCalc.inverse();
        QRCalc.inverse();
        swap(QLCalc, QRCalc);
        dirLR = inverseDirLR(dirLR);
    }

    if(debugMode){
        logger.log("Calculation quantities");
        logger.log("QLCalc", QLCalc.toString());
        logger.log("QRCalc", QRCalc.toString());
    }

    GSFlow FR = GSFlow(QRCalc);

    // only SL, GL cases are considered
    double xs = (solidCase(config) ? QLCalc.volumeFraction() - 1 : QRCalc.volumeFraction()) * dx;
    double vs = QRCalc.getSolidVelocity();
    double t1 = -xs/ifZero(vs, eps);
    double tau1 = t1>=0 && t1<=dt ? t1/dt : 1.0;

    GSQuantity QL_avg = (QLCalc + QRCalc) / (QLCalc.volumeFraction() + QRCalc.volumeFraction());
    GSFlow FL = GSFlow(QL_avg);

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

    GSFlow FStar = FL + sl * toFlow(QStar - QL_avg);

    GSFlow FBorder = solidCase(config) ?
            (FL*(1.0-tau2) + FStar * (tau2 - tau1))*dt :
            (FL*tau2 + FStar * (tau1 - tau2))*dt ;

    GSFlow flow = FBorder;

    if(debugMode){
        logger.log("Calculation values");
        logger.log("xs", to_string(xs));
        logger.log("vs", to_string(vs));
        logger.log("t1", to_string(t1));
        logger.log("tau1", to_string(tau1));
        logger.log("QLAvg", QL_avg.toString());
        logger.log("ul", to_string(ul));
        logger.log("al", to_string(al));
        logger.log("sl", to_string(sl));
        logger.log("t2", to_string(t2));
        logger.log("tau2", to_string(tau2));

        logger.log("Q* calculation:");
        logger.log("rhoL", to_string(rhoL));
        logger.log("pL", to_string(pL));
        logger.log("El", to_string(El));
        logger.log("Q*", QStar.toString());

        logger.log("F flows");
        logger.log("F*", FStar.toString());
        logger.log("F", flow.toString());
    }

    double n = leftDiscontinuousCase(config) ? -1.0 : 1.0;
    GSFlow G = n * (FStar - vs* toFlow(QStar));

    GSFlow GMinus = solidCase(config) ? G*tau1*dt : G*(1.0-tau1)*dt;
    GSFlow GPlus = solidCase(config) ? G*(1.0-tau1)*dt : G*tau1*dt;

    if(debugMode){
        logger.log("G flows");
        logger.log("n", to_string(n));
        logger.log("G", G.toString());
        logger.log("G-", GMinus.toString());
        logger.log("G+", GPlus.toString());
    }

    if(solidCase(config)){
        double t3 = (-dx - xs)/ifZero(vs, eps);
        double tau3 = t3>=0 && t3<=dt ? t3/dt : 1.0;
        GMinus *= tau3;
        if(debugMode){
            logger.log("t3", to_string(t3));
            logger.log("tau3", to_string(tau3));
            logger.log("G-", GMinus.toString());
            logger.log("G+", GPlus.toString());
        }
    } else {
        double t3 = (dx - xs)/ifZero(vs, eps);
        double tau3 = t3>=0 && t3<=dt ? t3/dt : 1.0;
        GPlus *= tau3;
        if(debugMode){
            logger.log("t3", to_string(t3));
            logger.log("tau3", to_string(tau3));
            logger.log("G-", GMinus.toString());
            logger.log("G+", GPlus.toString());
        }
    }

    if(solidCase(config)){
        GMinus *= 0.0;
    }

    if(rightDiscontinuousCase(config)) {
        flow.inverse();
        GMinus.inverse();
        GPlus.inverse();
        swap(GMinus, GPlus);
    }

    if(debugMode){
        logger.log("after switching config back");
        logger.log("F", flow.toString());
        logger.log("G-", GMinus.toString());
        logger.log("G+", GPlus.toString());
    }

    return {flow, GMinus, GPlus};
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
    double tau2 = -xs/ifZero(vs, eps)/dt;
    tau2 = 1.0 + (H(tau2) - H(tau2 - 1.0))*(tau2 - 1.0);

    GSQuantity QL_avg = gasCase(config) ?
                        QLCalc :
                        (QLCalc + QRCalc) / (QLCalc.volumeFraction() + QRCalc.volumeFraction());


    double ul = QL_avg.velocity();
    double al = QL_avg.soundSpeed();
    double sl = CRPSWave(ul, al, vs);
    double tau1 = -xs/ifZero(sl, eps)/dt;
    tau1 = 1.0 + (H(tau1) - H(tau1 - 1.0))*(tau1 - 1.0);

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

    GSFlow F1 = (FStar * (tau2 - tau1) + GSFlow(QL_avg)*(1.0-tau2))*dt;
    GSFlow F2 = (FStar * (tau1 - tau2) + GSFlow(QL_avg)*tau2)*dt;
    GSFlow FBorder = F1 + H(xs)*(F2 - F1);

    GSFlow G = -1.0 * (FStar - vs* toFlow(QStar));

    GSFlow G1 = G * tau1 * dt;
    GSFlow G2 = G * (1.0 - tau1) * dt;
    GSFlow GMinus = G1 + H(xs)*(G2 - G1);
    GSFlow GPlus = G2 + H(xs)*(G1 - G2);

    GSFlow flow = FBorder;
    if(solidCase(config)){
        GMinus *= 0.0;
    }

    if(dirLR == R){
        flow -= GMinus;
    } else if (dirLR == L) {
        flow += GPlus;
    }

    if(rightDiscontinuousCase(config))
        flow.inverse();

    return flow;
}

GSFlow CRPnoPaddingMastering(const GSQuantity& QL, const GSQuantity& QR, double dt, double eps, int dirLR){
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

    GSFlow FL = GSFlow(QLCalc);
    GSFlow FR = GSFlow(QRCalc);

    GSFlow FStar = FL + sl * toFlow(QStar - QLCalc);

    GSFlow FBorder = (FL + (FStar - FL)*H(-sl) + (FR - FStar)*H(-vs))*dt;

    GSFlow flow = FBorder;

    GSFlow G = -1.0 * (FStar - vs* toFlow(QStar)) * dt;
    GSFlow GMinus = G * (1.0 - H0(-vs)) * dt;
    GSFlow GPlus = G * H0(-vs) * dt;

    if(dirLR == R){
        flow -= GMinus;
    } else if (dirLR == L) {
        flow += GPlus;
    }

    if(QL.isSolid(eps))
        flow.inverse();

    return flow;
}