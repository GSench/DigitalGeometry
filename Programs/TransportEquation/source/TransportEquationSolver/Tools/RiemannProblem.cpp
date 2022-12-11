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
