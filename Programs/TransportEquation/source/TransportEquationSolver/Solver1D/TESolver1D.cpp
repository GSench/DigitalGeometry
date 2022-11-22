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

template<typename T>
void TESolverStep(Quantity<T> &f,
                  VectorField1D &u,
                  TESolver1DParams &p){
    Quantity<T> currentQuantity = f;
    for (int i = 0; i < p.getCellCount(); i++) {

        f.setQuantity()
    }
}

template<typename T>
void SolveTransportEquation1D(Quantity<T> &f,
                              VectorField1D &u,
                              TESolver1DParams &p,
                              TESolver1DOutput &output) {
    output.print(f, 0, p.getDx());
    for (int n = 0; n < p.getNTimeSteps(); n++) {
        TESolverStep(f, u, p);
        output.print(f, n+1, p.getDx());
    }
}
