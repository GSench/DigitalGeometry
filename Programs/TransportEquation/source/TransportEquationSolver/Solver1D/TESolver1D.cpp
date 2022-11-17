#include <cmath>
#include <vector>
#include <functional>

#include "TESolver1D.h"
#include "../Tools/InterpolationFunctions.h"
#include "../../math/MathUtils.h"

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
             double dt,
             const vector<function<double(double)>> &Psy){ // 3 functions: {Psy|i-1 , Psy|i , Psy|i+1}
    double fiR = flow(Psy[1], Psy[2], ci.xR, ui.uR, dt);
    double fiL = flow(Psy[0], Psy[1], ci.xL, ui.uL, dt);
    return fi.fi - 1.0 / ci.dx * (fiR*ui.uR - fiL*ui.uL) * dt;
}

void TESolverStep(LineInterface &f,
                  LineInterface &u,
                  TESolver1DParams &p){
    vector<function<double(double)>> Psy(p.getCellCount()+2);
    for(int i=-1; i<p.getCellCount()+1; i++){
        int sgnUi = 0;
        if(i==-1) //TODO extend u outside area like f
            sgnUi = sgn(u[0]);
        else if(i==p.getCellCount())
            sgnUi = sgn(u[i]);
        else
            sgnUi = sgn((u[i]+u[i+1])/2.);
        F1D fi = getFi(f, i);
        C1D ci = getCi(p.getDx(), i);
        if(sgnUi<0){
            F1D invFi = inverse(fi);
            C1D invCi = inverse(ci);
            Psy[i+1] = fInverseX(p.getFlowInterpolationFunctionBuilder()(invFi, invCi));
        } else {
            Psy[i+1] = p.getFlowInterpolationFunctionBuilder()(fi, ci);
        }
    }


    double fiPrev = f[-1];
    double fiAfterLast = f[p.getCellCount()];

    for (int i = 0; i < p.getCellCount()-1; i++) { // calculating all cells except last
        F1D fi = getFi(f, i);
        fi.fiPrev = fiPrev; // using saved fi as fiPrev in the next cell
        fiPrev = fi.fi;
        f.set(i, fNext(fi, getUi(u, i), getCi(p.getDx(), i), p.getDt(),
                       {Psy[i], Psy[i+1], Psy[i+2]}));
    }
    // fiNext for last cell is old f0, so we calc this separately
    int iLast = p.getCellCount()-1;
    F1D fiLast = {f[iLast], fiPrev, fiAfterLast};
    f.set(iLast, fNext(fiLast, getUi(u, iLast), getCi(p.getDx(), iLast), p.getDt(), {Psy[iLast], Psy[iLast+1], Psy[iLast+2]}));
}

void SolveTransportEquation1D(Area1D &f,
                              VectorField1D &u,
                              TESolver1DParams &p,
                              TESolver1DOutput &output) {
    output.print(f, 0, p.getDx());
    for (int n = 0; n < p.getNTimeSteps(); n++) {
        TESolverStep(f, u, p);
        output.print(f, n+1, p.getDx());
    }
}
