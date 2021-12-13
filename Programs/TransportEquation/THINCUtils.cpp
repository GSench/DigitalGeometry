#include <math.h>

#include "THINCUtils.h"

double getGamma(double fiNext, double fiPrev) {
    double deltaFi = fiNext - fiPrev;
    if (deltaFi < 0) return -1;
    else if (deltaFi > 0) return 1;
    else return 0;
}

double getAlpha(double fiNext, double fiPrev) {
    return fiNext >= fiPrev ? fiNext : fiPrev;
}

double getXiavg(double beta, double gamma, double fi) {
    return 1. / 2 / beta * log(exp(beta / gamma * (1 + gamma - 2 * fi)) / (1 - exp(beta / gamma * (1 - gamma - 2 * fi))));
}

bool calcCondition(double fiPrev, double fi, double fiNext, double eps) {
    return (
            fi > eps && fi < 1 - eps //(i)
            &&
            (fiNext - fi) * (fi - fiPrev)>0 //(ii)
    );
}

std::function<double(double)> Fi(double beta, double gamma, double xiLeft, double deltaXi, double xiavg) {
    return [=](double x)->double {
        return 1 / 2. * (1 + gamma * tanh(beta * ((x - xiLeft) / deltaXi - xiavg)));
    };
}
