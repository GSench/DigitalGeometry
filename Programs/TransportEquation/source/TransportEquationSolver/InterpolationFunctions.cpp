#include <vector>
#include <functional>

#include "../math/MathUtils.h"
#include "THINCUtils.h"

using namespace std;

function<double(double)> PsyGodunov(const vector<double>& f, int i, double beta, double h, double eps) {
    return [=](double x)->double {
        return f[i];
    };
}

function<double(double)> PsyMUSCL(const vector<double>& f, int i, double beta, double h, double eps) {
    int iPrev = i != 0 ? i - 1 : f.size() - 1;
    int iNext = i != f.size() - 1 ? i + 1 : 0;

    double fi = f[i];
    double fiPrev = f[iPrev];
    double fiNext = f[iNext];

    double dfR = (fiNext - fi) / h;
    double dfL = (fi - fiPrev) / h;

    double k = minmod(dfL, dfR);
    double b = fi - k * (i + 0.5) * h;

    return [=](double x)->double {
        return k * x + b;
    };
}

function<double(double)> PsyTHINCandGodunov(const vector<double>& f, int i, double beta, double h, double eps) {

    int iPrev = i != 0 ? i - 1 : f.size() - 1;
    int iNext = i != f.size() - 1 ? i + 1 : 0;

    double xL = i * h;
    double xR = (i + 1) * h;

    double fi = f[i];
    double fiPrev = f[iPrev];
    double fiNext = f[iNext];

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

function<double(double)> PsyTHINCandMUSCL(const vector<double>& f, int i, double beta, double h, double eps) {

    int iPrev = i != 0 ? i - 1 : f.size() - 1;
    int iNext = i != f.size() - 1 ? i + 1 : 0;

    double xL = i * h;
    double xR = (i + 1) * h;

    double fi = f[i];
    double fiPrev = f[iPrev];
    double fiNext = f[iNext];

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