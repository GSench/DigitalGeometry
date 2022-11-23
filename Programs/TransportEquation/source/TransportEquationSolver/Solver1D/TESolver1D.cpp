#include "TESolver1D.h"
#include "../../math/MathUtils.h"

using namespace std;

template<typename T>
void updateCell(Quantity<T> &f,
                Velocity &u,
                TESolver1DParams<T> &p){
    T fL = p.getFlow().calc(f.prev(), f, p.getDt(), u);
    T fR = p.getFlow().calc(f, f.next(), p.getDt(), u.next());
    T fNext = f.getQuantity() - p.getDt() / 2. / f.dx() * (fR - fL);
    f.setQuantity(fNext);
}

template<typename T>
void TESolverStep(Quantity<T> &f,
                  Velocity &u,
                  TESolver1DParams<T> &p){
    do {
        updateCell<T>(f, u, p);
        f = f.next();
        u = u.next();
    }
    while (!f.isBorder());
    updateCell<T>(f, u, p);
}

template<typename T>
void SolveTransportEquation1D(Quantity<T> &f,
                              Velocity &u,
                              TESolver1DParams<T> &p//,
                              //TESolver1DOutput &output
                              ) {
    //output.print(f, 0, p.getDx());
    for (int n = 0; n < p.getNTimeSteps(); n++) {
        TESolverStep(f, u, p);
        //output.print(f, n+1, p.getDx());
    }
}
