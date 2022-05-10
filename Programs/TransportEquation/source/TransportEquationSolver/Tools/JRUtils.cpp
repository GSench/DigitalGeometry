//
// Created by gsench on 10.05.22.
//

#include "JRUtils.h"

double H(double x){
    if(x>=0) return 1;
    else return 0;
}

std::function<double(double)> FiJR(double gamma, double xiavg) {
    return [=](double x)->double {
        return (1-gamma)/2.+gamma*H(x-xiavg);
    };
}

double getXiavgJR(double xiRight, double deltaXi, double gamma, double fi, double fiMin, double deltaFi){
    return xiRight - deltaXi * ((fi-fiMin)/deltaFi/gamma - (1.-gamma)/2./gamma);
}

