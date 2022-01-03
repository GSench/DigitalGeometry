#include <vector>
#include <functional>

#include "../math/MathUtils.h"
#include "THINCUtils.h"

using namespace std;

function<double(double)> PsyGodunov(double fi) {
    return [=](double x)->double {
        return fi;
    };
}

function<double(double)> PsyMUSCL(double fi, double fiPrev, double fiNext, int i, double h) {
    double dfR = (fiNext - fi) / h;
    double dfL = (fi - fiPrev) / h;

    double k = minmod(dfL, dfR);
    double b = fi - k * (i + 0.5) * h;

    return [=](double x)->double {
        return k * x + b;
    };
}

function<double(double)> PsyTHINCandGodunov(double fi, double fiPrev, double fiNext, int i, double beta, double h, double eps) {
    double xL = i * h;
    //double xR = (i + 1) * h;

    double fiMin = min(fiPrev, fiNext);
    double fiMax = max(fiPrev, fiNext);
    double deltaFi = fiMax - fiMin;

    if (!calcCondition(fiPrev, fi, fiNext, eps))
        return [=](double x)->double {
        return fi; //Godunov
    };

    double gamma = getGamma(fiNext, fiPrev);
    double xiavg = getXiavg(beta, gamma, fi);

    return [=](double x)->double {
        return fiMin + (Fi)(beta, gamma, xL, h, xiavg)(x) * deltaFi;
    };
}

function<double(double)> PsyTHINCandMUSCL(double fi, double fiPrev, double fiNext, int i, double beta, double h, double eps) {
    double xL = i * h;
    //double xR = (i + 1) * h;

    double fiMin = min(fiPrev, fiNext);
    double fiMax = max(fiPrev, fiNext);
    double deltaFi = fiMax - fiMin;

    if (!calcCondition(fiPrev, fi, fiNext, eps)) {
        double dfR = (fiNext - fi) / h;
        double dfL = (fi - fiPrev) / h;

        double k = minmod(dfL, dfR);
        double b = fi - k * (i + 0.5) * h;

        return [=](double x)->double {
            return k * x + b;
        };
    }

    double gamma = getGamma(fiNext, fiPrev);
    double xiavg = getXiavg(beta, gamma, fi);

    return [=](double x)->double {
        return fiMin + (Fi)(beta, gamma, xL, h, xiavg)(x) * deltaFi;
    };
}

double getXforInterpolation(double x, double u, double t){
    return x - u * t;
}