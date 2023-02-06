//
// Created by grigoriy.senchenok on 09.12.2022.
//

#include "RiemannProblem.h"
#include "../../math/MathUtils.h"

pair<double, double> RPWaves(double ul, double ur, double al, double ar){
    return {
        /*sl=*/min(0., min(ul-al, avg<double>({ul,ur})-avg<double>({al,ar}))),
        /*sr=*/max(0., max(ar+ar, avg<double>({ul,ur})+avg<double>({al,ar})))
    };
}

double RPRBWave(double ul, double al, double vs){
    return /*sl=*/min(0., min(ul-al, vs-al));
}

GSFlow RP(const GSQuantity& QL, const GSQuantity& QR, double dt){
    GSFlow FL(QL);
    GSFlow FR(QR);
    pair<double,double> slr = RPWaves(QL.velocity(), QL.velocity(), QL.soundSpeed(), QR.soundSpeed());
    double sl = slr.first;
    double sr = slr.second;
    if(sl>0) return FL;
    if(sr<0) return FR;
    GSFlow FDiscontinuity = (sl*FL - sl*FR + sl*sr*convertQuantity(QR-QL))/(sr-sl);
    return FDiscontinuity*dt;
}