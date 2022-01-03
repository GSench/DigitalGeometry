//
// Created by grigoriy.senchenok on 21.12.2021.
//

#include "StandardSolver.h"

#include <math.h>
#include <vector>
#include <functional>

using namespace std;

// ------------------------ MathUtils ---------------------------------
template <typename T> int sgnDebug(T val) {
    return (T(0) < val) - (val < T(0));
}
double minmodDebug(double x, double y) {
    if (x * y < 0) return 0;
    else return sgnDebug(x) * min(abs(x), abs(y));
}

// ------------------------ THINC Utils -------------------------------
double getGammaDebug(double fiNext, double fiPrev) {
    double deltaFi = fiNext - fiPrev;
    if (deltaFi < 0) return -1;
    else if (deltaFi > 0) return 1;
    else return 0;
}
double getXiavgDebug(double beta, double gamma, double fi) {
    return 1. / 2 / beta * log(exp(beta / gamma * (1 + gamma - 2 * fi)) / (1 - exp(beta / gamma * (1 - gamma - 2 * fi))));
}
bool calcConditionDebug(double fiPrev, double fi, double fiNext, double eps) {
    return (
            fi > eps && fi < 1 - eps //(i)
            &&
            (fiNext - fi) * (fi - fiPrev)>0 //(ii)
    );
}
std::function<double(double)> FiDebug(double beta, double gamma, double xiLeft, double deltaXi, double xiavg) {
    return [=](double x)->double {
        return 1 / 2. * (1 + gamma * tanh(beta * ((x - xiLeft) / deltaXi - xiavg)));
    };
}

// ------------------------- Interpolation Functions ------------------
function<double(double)> PsyGodunovDebug(const vector<double>& f, int i, double beta, double h, double eps) {
    return [=](double x)->double {
        return f[i];
    };
}
function<double(double)> PsyMUSCLDebug(const vector<double>& f, int i, double beta, double h, double eps) {
    int iPrev = i != 0 ? i - 1 : f.size() - 1;
    int iNext = i != f.size() - 1 ? i + 1 : 0;

    double fi = f[i];
    double fiPrev = f[iPrev];
    double fiNext = f[iNext];

    double dfR = (fiNext - fi) / h;
    double dfL = (fi - fiPrev) / h;

    double k = minmodDebug(dfL, dfR);
    double b = fi - k * (i + 0.5) * h;

    return [=](double x)->double {
        return k * x + b;
    };
}
function<double(double)> PsyTHINCandGodunovDebug(const vector<double>& f, int i, double beta, double h, double eps) {

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

    if (!calcConditionDebug(fiPrev, fi, fiNext, eps))
        return [=](double x)->double {
            return fi; //Godunov
        };

    double gamma = getGammaDebug(fiNext, fiPrev);
    double xiavg = getXiavgDebug(beta, gamma, fi);

    return [=](double x)->double {
        return fiMin + (FiDebug)(beta, gamma, xL, h, xiavg)(x) * deltaFi;
    };
}
function<double(double)> PsyTHINCandMUSCLDebug(const vector<double>& f, int i, double beta, double h, double eps) {

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

    if (!calcConditionDebug(fiPrev, fi, fiNext, eps)) {
        double dfR = (fiNext - fi) / h;
        double dfL = (fi - fiPrev) / h;

        double k = minmodDebug(dfL, dfR);
        double b = fi - k * (i + 0.5) * h;

        return [=](double x)->double {
            return k * x + b;
        };
    }

    double gamma = getGammaDebug(fiNext, fiPrev);
    double xiavg = getXiavgDebug(beta, gamma, fi);

    return [=](double x)->double {
        return fiMin + (FiDebug)(beta, gamma, xL, h, xiavg)(x) * deltaFi;
    };
}

// ------------------------- Standard Solver ---------------------------
double THINC1DDebug(const THINC1DparamsDebug& p, vector<double> &f, const vector<double>& fexact) {
    double h = p.area / p.cellCount;
    double timeStep = p.CFL * h / p.u;

    vector<double> fnext = f;

    for (int n = 0; n < p.stepN; n++) {

        //first previous Psy is from last cell (cycled space)
        function<double(double)> PsyPrevVirt = p.PsyFunc(f, p.cellCount - 1, p.beta, h, p.eps);
        function<double(double)> PsyPrev = [=](double x)->double {
            return PsyPrevVirt(x+p.cellCount*h);
        };

        for (int i = 0; i < p.cellCount; i++) {
            int iPrev = i != 0 ? i - 1 : p.cellCount - 1;
            int iNext = i != p.cellCount - 1 ? i + 1 : 0;

            double fi = f[i];
            double fiPrev = f[iPrev];
            double fiNext = f[iNext];
            double xL = i * h;
            double xR = (i + 1) * h;

            function<double(double)> Psy = p.PsyFunc(f, i, p.beta, h, p.eps);

            double fiR = Psy(xR - p.u * timeStep / 2); //flow on right cell side is from current cell (upwind)
            double fiL = PsyPrev(xL - p.u * timeStep / 2); //flow on left cell side is from previous cell (upwind)
            fnext[i] = fi - 1.0 / h * (fiR * p.u - fiL * p.u) * timeStep;

            PsyPrev = Psy;
        }
        for (int i = 0; i < p.cellCount; i++) {
            f[i] = fnext[i];
        }
    }

    double error = 0;
    for (int i = 0; i < p.cellCount; i++) {
        error += pow(f[i]*h - fexact[i] * h, 2);
    }
    error = sqrt(error);
    return error;
}
