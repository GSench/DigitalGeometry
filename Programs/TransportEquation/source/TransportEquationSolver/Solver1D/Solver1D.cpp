#include <cmath>
#include <vector>
#include <functional>

#include "Solver1D.h"
#include "../InterpolationFunctions.h"
#include "Solver1DOutput.h"
#include "VectorField1D.h"
#include "Solver1DParams.h"

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

double fNext(Area1D p,
             F1D c,
             function<double(double)> &PsyPrev){
    double timeStep = p.timeStep();
    function<double(double)> Psy = p.FlowInterpolationFunction(c.fi, c.fiPrev, c.fiNext, c.i, c.h);

    double fiR = Psy(getXforInterpolation(c.xR, c.uR, timeStep / 2)); //flow on right cell side is from current cell (upwind)
    double fiL = PsyPrev(getXforInterpolation(c.xL, c.uL, timeStep / 2)); //flow on left cell side is from previous cell (upwind)
    PsyPrev = Psy;
    return c.fi - 1.0 / c.h * (fiR*c.uR - fiL*c.uL) * timeStep;
}

void SolverStep(Area1D p,
                vector<double> &f,
                const vector<double>& u05t){
    double h = p.h();

    function<double(double)> PsyPrev = [=](double x)->double {
        return 0;
    };
    if(p.periodicBoundaries){
        //first previous Psy is from last cell (cycled space)
        function<double(double)> PsyPrevVirt = p.FlowInterpolationFunction(
                f[p.cellCount - 1],
                f[p.cellCount - 2],
                f[0],
                p.cellCount - 1,
                h); // this func is built on last cell, will give wrong value in first cell
        PsyPrev = [=](double x)->double {
            return PsyPrevVirt(x+p.cellCount*h); // PsyPrev just shifts PsyPrevVirt
        };
    }

    double fiPrev = 0;
    double fiAfterLast = 0;
    if(p.periodicBoundaries){
        fiPrev = f[p.cellCount - 1]; // fiPrev for 1st cell is fi in the last cell
        fiAfterLast = f[0]; // saving old value of f0, to use it as fiNext in the last cell
    }
    for (int i = 0; i < p.cellCount-1; i++) { // calculating all cells except last
        F1D cell1D{i, h, f[i], fiPrev, f[i + 1], i * h, (i + 1) * h, u05t[i], u05t[i + 1]};
        double saveFi = f[i]; // saving old value of each fi, to use it as fiPrev in the next cell
        f[i] = fNext(p, cell1D, PsyPrev);
        fiPrev = saveFi; // using saved fi as fiPrev in the next cell
    }
    // fiNext for last cell is old f0, so we calc this separately
    int iLast = p.cellCount-1;
    F1D cell1D{iLast, h, f[iLast], fiPrev, fiAfterLast, iLast * h, (iLast + 1) * h, u05t[iLast], u05t[iLast + 1]};
    f[iLast] = fNext(p, cell1D, PsyPrev);
}

void SolveTransportEquation1D(const Area1D& f,
                              const VectorField1D& u,
                              const Solver1DParams& params, // uMax(t): uMax(n + 1/2)[i +- 1/2]: velocity vector field at half of time steps: uMax(0) is at t=0, uMax(1) is at t=dt/2, uMax(2) is at t=dt, uMax(2*n) is at t=n*dt
                              // velocity vector field on cells' bounds: uMax[0] is in x=0: left side of 0s cell, uMax[1] is in x=dx: right side of 0s cell, left side of 1st cell
                              Solver1DOutput& output) {
    output.print(f, 0, p.h());
    for (int n = 0; n < p.NTimeSteps; n++) {
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