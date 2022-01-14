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

double fNext(F1D f,
             U1D u,
             function<double(double)> &PsyPrev){
    double timeStep = p.timeStep();
    function<double(double)> Psy = p.FlowInterpolationFunction(c.fi, c.fiPrev, c.fiNext, c.i, c.h);

    double fiR = Psy(getXforInterpolation(c.xR, c.uR, timeStep / 2)); //flow on right cell side is from current cell (upwind)
    double fiL = PsyPrev(getXforInterpolation(c.xL, c.uL, timeStep / 2)); //flow on left cell side is from previous cell (upwind)
    PsyPrev = Psy;
    return c.fi - 1.0 / c.h * (fiR*c.uR - fiL*c.uL) * timeStep;
}

void SolverStep(LineInterface& f,
                VectorField1D& u,
                const Solver1DParams& p){

    function<double(double)> PsyPrev = [=](double x)->double {
        return 0;
    };
    if(f.hasPeriodicBoundaries()){
        //first previous Psy is from last cell (cycled space)
        f.startIteration();
        f.moveToLast();
        function<double(double)> PsyPrevVirt = p.FlowInterpolationFunction(f.getCurrent(), f.getCurrentCell(p.dx));
        // this func is built on last cell, will give wrong value in first cell
        PsyPrev = [=](double x)->double {
            return PsyPrevVirt(x+p.areaLength); // PsyPrev just shifts PsyPrevVirt
        };
    }

    // PREV PROBLEM!!!
    for (f.startIteration(), u.startIteration(); !f.isFinished(); f.moveNext(), u.moveNext()) {
        F1D saveFi = f.getCurrent(); // saving old value of each fi, to use it as fiPrev in the next cell
        f.setCurrent(fNext(f.getCurrent(), u.getCurrent(), PsyPrev));
        fiPrev = saveFi; // using saved fi as fiPrev in the next cell
    }
    // fiNext for last cell is old f0, so we calc this separately
    int iLast = p.cellCount-1;
    F1D cell1D{iLast, h, f[iLast], fiPrev, fiAfterLast, iLast * h, (iLast + 1) * h, u05t[iLast], u05t[iLast + 1]};
    f[iLast] = fNext(p, cell1D, PsyPrev);
}

void SolveTransportEquation1D(LineInterface& f,
                              const VectorField1D& u,
                              const Solver1DParams& p, // velocity vector field on cells' bounds: uMax[0] is in x=0: left side of 0s cell, uMax[1] is in x=dx: right side of 0s cell, left side of 1st cell
                              Solver1DOutput& output) {
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