#include <vector>
#include <functional>

#include "TERBSolver1D.h"
#include "../../math/MathUtils.h"

using namespace std;

double flow(const function<double(double)>& PsyL,
            const function<double(double)>& PsyR,
            double x, RBVectorField1D u, double dt){
    const function<double(double)>& Psy = u.direction()>=0 ? PsyL : PsyR;
    return u.getU()*Psy(x)+u.getUNext()*Psy(x-dt*(u.getUNext()+u.getU())/2.);
}

double fNext(F1D fi,
             RBVectorField1D u,
             C1D ci,
             double dt,
             const vector<function<double(double)>> &Psy){ // 3 functions: {Psy|i-1 , Psy|i , Psy|i+1}
    double fiR = flow(Psy[1], Psy[2], ci.xR, u, dt);
    double fiL = flow(Psy[0], Psy[1], ci.xL, u, dt);
    return fi.fi - dt / 2. / ci.dx  * (fiR - fiL);
}

void TERBSolverStep(LineInterface &f,
                    RBVectorField1D &u,
                    TESolver1DParams &p){
    vector<function<double(double)>> Psy(p.getCellCount()+2);
    for(int i=-1; i<p.getCellCount()+1; i++){
        F1D fi = getFi(f, i);
        C1D ci = getCi(p.getDx(), i);
        if(u.direction()<0){
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
        f.set(i, fNext(fi, u, getCi(p.getDx(), i), p.getDt(),
                       {Psy[i], Psy[i+1], Psy[i+2]}));
    }
    // fiNext for last cell is old f0, so we calc this separately
    int iLast = p.getCellCount()-1;
    F1D fiLast = {f[iLast], fiPrev, fiAfterLast};
    f.set(iLast, fNext(fiLast, u, getCi(p.getDx(), iLast), p.getDt(), {Psy[iLast], Psy[iLast+1], Psy[iLast+2]}));
}

void SolveTransportEquationRB1D(Area1D &f,
                              RBVectorField1D &u,
                              TESolver1DParams &p,
                              TESolver1DOutput &output) {
    output.print(f, 0, p.getDx());
    for (int n = 0; n < p.getNTimeSteps(); n++) {
        TERBSolverStep(f, u, p);
        output.print(f, n+1, p.getDx());
    }
}
