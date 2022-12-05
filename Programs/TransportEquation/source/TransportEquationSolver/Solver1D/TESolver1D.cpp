#include "TESolver1D.h"

using namespace std;

template<typename F, typename U>
void updateCell(Quantity<F> &f,
                Quantity<U> &u,
                TESolver1DParams<F,U> &p){
    F fL = p.getFlow().calc(f.prev(), f, p.getDt(), u);
    F fR = p.getFlow().calc(f, f.next(), p.getDt(), u.next());
    F fNext = f.getQuantity() - 1. / f.dx() * (fR - fL);
    f.setQuantity(fNext);
}

template<typename F, typename U>
void TESolverStep(Quantity<F>& f,
                  Quantity<U>& u,
                  TESolver1DParams<F,U>& p){
    Quantity<F>* fIter = &f;
    Quantity<U>* uIter = &u;
    do {
        updateCell<F,U>(fIter, uIter, p);
        fIter = fIter->next();
        uIter = uIter->next();
    }
    while (!f.isBorder());
    updateCell<F,U>(fIter, uIter, p);
}

template<typename F, typename U>
void SolveTransportEquation1D(Quantity<F>& f,
                              Quantity<U>& u,
                              TESolver1DParams<F,U>& p,
                              TESolver1DOutput<F,U> &output
                              ) {
    output.print(f, 0);
    for (int n = 0; n < p.getNTimeSteps(); n++) {
        TESolverStep<F,U>(f, u, p);
        f.apply();
        output.print(f, n+1);
    }
}
