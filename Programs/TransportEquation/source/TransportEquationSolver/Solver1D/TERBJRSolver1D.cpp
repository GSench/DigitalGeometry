#include <vector>
#include <functional>

#include "TERBJRSolver1D.h"
#include "../../math/MathUtils.h"
#include "../Tools/THINCUtils.h"
#include "../Tools/JRUtils.h"

using namespace std;

double fNext(F1D fi, F1D fiPrev, F1D fiNext,
             RBVectorField1D u,
             C1D ci,
             double dt) {
    double fiL = 0;
    double fiR = 0;
    double uiHalfNext = (u.getU() + u.getUNext())/2.;
    if(u.direction()>0){
        if(calcCondition(fi.fiPrev, fi.fi, fi.fiNext, 1e-4)){
            double fiMin = min(fi.fiPrev, fi.fiNext);
            double fiMax = max(fi.fiPrev, fi.fiNext);
            double deltaFi = fiMax - fiMin;
            double gamma = getGamma(fi.fiNext, fi.fiPrev);
            double xJump = getXiavgJR(ci.xR, ci.dx, gamma, fi.fi, fiMin, deltaFi);
            double tJump = (ci.xR - xJump)/u.getU();
            fiR = uiHalfNext * (fi.fiNext * min(dt, tJump) + fi.fiPrev * max(0., dt - tJump));
        } else {
            fiR = uiHalfNext * fi.fi * dt;
        }
        if(calcCondition(fiPrev.fiPrev, fiPrev.fi, fiPrev.fiNext, 1e-4)){
            double fiMin = min(fiPrev.fiPrev, fiPrev.fiNext);
            double fiMax = max(fiPrev.fiPrev, fiPrev.fiNext);
            double deltaFi = fiMax - fiMin;
            double gamma = getGamma(fiPrev.fiNext, fiPrev.fiPrev);
            double xJump = getXiavgJR(ci.xL, ci.dx, gamma, fiPrev.fi, fiMin, deltaFi);
            double tJump = (ci.xL - xJump)/u.getU();
            fiL = uiHalfNext * (fiPrev.fiNext * min(dt, tJump) + fiPrev.fiPrev * max(0., dt - tJump));
        } else {
            fiL = uiHalfNext * fiPrev.fi * dt;
        }
    } else {
        if(calcCondition(fiNext.fiPrev, fiNext.fi, fiNext.fiNext, 1e-4)){
            double fiMin = min(fiNext.fiPrev, fiNext.fiNext);
            double fiMax = max(fiNext.fiPrev, fiNext.fiNext);
            double deltaFi = fiMax - fiMin;
            double gamma = getGamma(fiNext.fiNext, fiNext.fiPrev);
            double xJump = getXiavgJR(ci.xR, ci.dx, gamma, fiNext.fi, fiMin, deltaFi);
            double tJump = (ci.xR - xJump)/u.getU();
            fiR = uiHalfNext * (fiNext.fiNext * min(dt, tJump) + fiNext.fiPrev * max(0., dt - tJump));
        } else {
            fiR = uiHalfNext * fiNext.fi * dt;
        }
        if(calcCondition(fi.fiPrev, fi.fi, fi.fiNext, 1e-4)){
            double fiMin = min(fi.fiPrev, fi.fiNext);
            double fiMax = max(fi.fiPrev, fi.fiNext);
            double deltaFi = fiMax - fiMin;
            double gamma = getGamma(fi.fiNext, fi.fiPrev);
            double xJump = getXiavgJR(ci.xL, ci.dx, gamma, fi.fi, fiMin, deltaFi);
            double tJump = (ci.xL - xJump)/u.getU();
            fiL = uiHalfNext * (fi.fiNext * min(dt, tJump) + fi.fiPrev * max(0., dt - tJump));
        } else {
            fiL = uiHalfNext * fi.fi * dt;
        }
    }
    return fi.fi - (fiR - fiL) / ci.dx;
}

void TERBJRSolverStep(LineInterface &f,
                    RBVectorField1D &u,
                    TESolver1DParams &p){

    vector<F1D> oldFi(p.getCellCount()+2);
    for(int i=-1; i<p.getCellCount()+1; i++){
        oldFi[i+1] = getFi(f, i);
    }

    for (int i = 0; i < p.getCellCount(); i++) { // calculating all cells except last
        f.set(i, fNext(oldFi[i+1], oldFi[i], oldFi[i+1], u, getCi(p.getDx(), i), p.getDt()));
    }

}

void SolveTransportEquationRBJR1D(Area1D &f,
                              RBVectorField1D &u,
                              TESolver1DParams &p,
                              TESolver1DOutput &output) {
    output.print(f, 0, p.getDx());
    for (int n = 0; n < p.getNTimeSteps(); n++) {
        TERBJRSolverStep(f, u, p);
        output.print(f, n+1, p.getDx());
    }
}
