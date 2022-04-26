#include <vector>
#include <functional>

#include "../../math/MathUtils.h"
#include "THINCUtils.h"
#include "../Instances/TESolver1DInstances.h"

using namespace std;

function<double(double)> PsyGodunov(double fi) {
    return [=](double x)->double {
        return fi;
    };
}

function<double(double)> PsyMUSCL(F1D f, C1D c) {
    double dfR = (f.fiNext - f.fi) / c.dx;
    double dfL = (f.fi - f.fiPrev) / c.dx;
    double k = minmod(dfL, dfR);
    double b = f.fi - k * c.x;
    return [=](double x)->double {
        return k * x + b;
    };
}

function<double(double)> PsyTHINC(F1D f, C1D c, double beta) {
    double fiMin = min(f.fiPrev, f.fiNext);
    double fiMax = max(f.fiPrev, f.fiNext);
    double deltaFi = fiMax - fiMin;
    double gamma = getGamma(f.fiNext, f.fiPrev);
    double xiavg = getXiavg(beta, gamma,f. fi);
    return [=](double x)->double {
        return fiMin + (Fi)(beta, gamma, c.xL, c.dx, xiavg)(x) * deltaFi;
    };
}

function<double(double)> PsyTHINCandGodunov(F1D f, C1D c, double beta, double eps) {
    if (!calcCondition(f.fiPrev, f.fi, f.fiNext, eps))
        return PsyGodunov(f.fi);
    else return PsyTHINC(f, c, beta);
}

function<double(double)> PsyTHINCandMUSCL(F1D f, C1D c, double beta, double eps) {
    if (!calcCondition(f.fiPrev, f.fi, f.fiNext, eps))
        return PsyMUSCL(f, c);
    else return PsyTHINC(f, c, beta);
}

double getXforInterpolation(double x, double u, double t){
    return x - u * t;
}