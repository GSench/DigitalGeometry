#include <cmath>
#include <vector>
#include <functional>

#include "Solver1D.h"
#include "../InterpolationFunctions.h"
#include "Solver1DOutput.h"

using namespace std;

struct Cell1D {
    int i;
    double h;
    double fi;
    double fiPrev;
    double fiNext;
    double xL;
    double xR;
    double uL;
    double uR;
};

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

double fNext(Solver1DParams p,
             Cell1D c,
             function<double(double)> &PsyPrev){
    double timeStep = p.timeStep();
    function<double(double)> Psy = p.PsyFunc(c.fi, c.fiPrev, c.fiNext, c.i, p.beta, c.h, p.eps);

    double fiR = Psy(getXforInterpolation(c.xR, c.uR, timeStep / 2)); //flow on right cell side is from current cell (upwind)
    double fiL = PsyPrev(getXforInterpolation(c.xL, c.uL, timeStep / 2)); //flow on left cell side is from previous cell (upwind)
    PsyPrev = Psy;
    return c.fi - 1.0 / c.h * (fiR*c.uR - fiL*c.uL) * timeStep;
}

void SolverStep(Solver1DParams p,
                vector<double> &f,
                const vector<double>& u05t){
    double h = p.h();
    //first previous Psy is from last cell (cycled space)
    function<double(double)> PsyPrevVirt = p.PsyFunc(
            f[p.cellCount - 1],
            f[p.cellCount - 2],
            f[0],
            p.cellCount - 1,
            p.beta,
            h,
            p.eps);
    function<double(double)> PsyPrev = [=](double x)->double {
        return PsyPrevVirt(x+p.cellCount*h);
    };

    double fiPrev = f[p.cellCount - 1];
    double fiFirst = f[0];
    for (int i = 0; i < p.cellCount-1; i++) {
        Cell1D cell1D{i, h, f[i], fiPrev, f[i+1], i*h, (i+1)*h, u05t[i], u05t[i+1]};
        double saveFi = f[i];
        f[i] = fNext(p, cell1D, PsyPrev);
        fiPrev = saveFi;
    }
    int iLast = p.cellCount-1;
    Cell1D cell1D{iLast, h, f[iLast], fiPrev, fiFirst, iLast*h, (iLast+1)*h};
    f[iLast] = fNext(p, cell1D, PsyPrev);
}

void SolveTransportEquation1D(Solver1DParams p,
                              vector<double> &f,
                              const function<vector<double>(int)> &u, // u(t): u(n + 1/2)[i +- 1/2]: velocity vector field at half of time steps: u(0) is at t=0, u(1) is at t=dt/2, u(2) is at t=dt, u(2*n) is at t=n*dt
                              // velocity vector field on cells' bounds: u[0] is in x=0: left side of 0s cell, u[1] is in x=dx: right side of 0s cell, left side of 1st cell
                              Solver1DOutput& output) {
    output.print(f, 0, p.h());
    for (int n = 0; n < p.stepN; n++) {
        SolverStep(p, f, u(2*n));
        output.print(f, n+1, p.h());
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