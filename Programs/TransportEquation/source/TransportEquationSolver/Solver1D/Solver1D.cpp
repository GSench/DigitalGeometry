#include <cmath>
#include <vector>
#include <functional>

#include "Solver1D.h"
#include "../InterpolationFunctions.h"

using namespace std;

void initF(vector<double> &f, int L, int R) {
    for (int i = 0; i < L; i++)
        f[i] = 0;
    f[L] = 1;
    for (int i = L + 1; i < R; i++)
        f[i] = 1;
    f[R] = 1;
    for (int i = R + 1; i < f.size(); i++)
        f[i] = 0;
}

double fNext(F1D fi,
             U1D ui,
             C1D ci,
             const Solver1DParams& p,
             function<double(double)> &PsyPrev){

    function<double(double)> Psy = p.FlowInterpolationFunction(fi, ci);

    double fiR = Psy(getXforInterpolation(ci.xR, ui.uR, p.dt / 2)); //flow on right cell side is from current cell (upwind)
    double fiL = PsyPrev(getXforInterpolation(ci.xL, ui.uL, p.dt / 2)); //flow on left cell side is from previous cell (upwind)
    PsyPrev = Psy;
    return fi.fi - 1.0 / p.dx * (fiR*ui.uR - fiL*ui.uL) * p.dt;
}

void SolverStep(LineInterface &f,
                LineInterface &u,
                Solver1DParams &p){

    function<double(double)> PsyPrev = p.FlowInterpolationFunction(getFi(f, -1), getCi(p, -1));
    /* Like standard solver:
    function<double(double)> PsyPrevVirt = p.FlowInterpolationFunction(getFi(f, p.cellCount-1), getCi(p, p.cellCount-1));
    function<double(double)> PsyPrev = [=](double x) -> double {
        return PsyPrevVirt(x+p.dx*p.cellCount);
    };*/

    double fiPrev = f[-1];
    double fiAfterLast = f[p.cellCount];

    for (int i = 0; i < p.cellCount-1; i++) { // calculating all cells except last
        F1D fi = getFi(f, i);
        fi.fiPrev = fiPrev; // using saved fi as fiPrev in the next cell
        fiPrev = fi.fi;
        f.set(i, fNext(fi, getUi(u, i), getCi(p, i), p, PsyPrev));
    }
    // fiNext for last cell is old f0, so we calc this separately
    int iLast = p.cellCount-1;
    F1D fiLast = {f[iLast], fiPrev, fiAfterLast};
    f.set(iLast, fNext(fiLast, getUi(u, iLast), getCi(p, iLast), p, PsyPrev));
}

void SolveTransportEquation1D(LineInterface &f,
                              LineInterface &u,
                              Solver1DParams &p,
                              Solver1DOutput &output) {
    output.print(f, 0, p.dx);
    for (int n = 0; n < p.NTimeSteps; n++) {
        SolverStep(f, u, p);
        output.print(f, n+1, p.dx);
    }
}

double errorL2(vector<double> &f, const vector<double>& fexact, double h){
    double error = 0;
    for (int i = 0; i < f.size(); i++) {
        error += pow(f[i]*h - fexact[i] * h, 2);
    }
    error = sqrt(error);
    return error;
}