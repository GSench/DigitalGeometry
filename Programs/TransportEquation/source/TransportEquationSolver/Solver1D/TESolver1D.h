#include "TESolver1DOutput.h"

template<typename F, typename U>
void TESolverStep(Quantity<F> &f,
                  Quantity<U> &u,
                  TESolver1DParams<F,U> &p
                  );

template<typename F, typename U>
void SolveTransportEquation1D(Quantity<F> &f,
                              Quantity<U> &u,
                              TESolver1DParams<F,U> &p,
                              TESolver1DOutput<F,U> &output
                              );
