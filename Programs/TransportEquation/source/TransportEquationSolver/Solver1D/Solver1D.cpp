#include <cmath>
#include <vector>
#include <functional>

#include "Solver1D.h"
#include "../InterpolationFunctions.h"

using namespace std;

double flow(const function<double(double)>& PsyL,
            const function<double(double)>& PsyR,
            double x, double u, double dt){
    return u>=0 ?
    PsyL(getXforInterpolation(x, u, dt/2)) :
    PsyR(getXforInterpolation(x, u, dt/2));
}

double fNext(F1D fi,
             U1D ui,
             C1D ci,
             const Solver1DParams& p,
             const vector<function<double(double)>> &Psy){ // 3 functions: {Psy|i-1 , Psy|i , Psy|i+1}
    double fiR = flow(Psy[1], Psy[2], ci.xR, ui.uR, p.dt);
    double fiL = flow(Psy[0], Psy[1], ci.xL, ui.uL, p.dt);
    return fi.fi - 1.0 / p.dx * (fiR*ui.uR - fiL*ui.uL) * p.dt;
}

void SolverStep(LineInterface &f,
                LineInterface &u,
                Solver1DParams &p){
    vector<function<double(double)>> Psy(p.cellCount+2);
    for(int i=-1; i<p.cellCount+1; i++)
        Psy[i+1] = p.FlowInterpolationFunction(getFi(f, i), getCi(p, i));

    double fiPrev = f[-1];
    double fiAfterLast = f[p.cellCount];

    for (int i = 0; i < p.cellCount-1; i++) { // calculating all cells except last
        if(i==766){
            int debug = 1;
        }
        F1D fi = getFi(f, i);
        fi.fiPrev = fiPrev; // using saved fi as fiPrev in the next cell
        fiPrev = fi.fi;
        f.set(i, fNext(fi, getUi(u, i), getCi(p, i), p,
                       {Psy[i], Psy[i+1], Psy[i+2]}));
    }
    // fiNext for last cell is old f0, so we calc this separately
    int iLast = p.cellCount-1;
    F1D fiLast = {f[iLast], fiPrev, fiAfterLast};
    f.set(iLast, fNext(fiLast, getUi(u, iLast), getCi(p, iLast), p, {Psy[iLast], Psy[iLast+1], Psy[iLast+2]}));
}

void SolveTransportEquation1D(Area1D &f,
                              VectorField1D &u,
                              Solver1DParams &p,
                              Solver1DOutput &output) {
    output.print(f, 0, p.dx);
    for (int n = 0; n < p.NTimeSteps; n++) {
        if(n==1099){
            int debug = 1;
        }
        SolverStep(f, u, p);
        output.print(f, n+1, p.dx);
    }
}

double errorL2(vector<double> f, const vector<double>& fexact, double h){
    double error = 0;
    for (int i = 0; i < f.size(); i++) {
        error += pow(f[i]*h - fexact[i] * h, 2);
    }
    error = sqrt(error);
    return error;
}