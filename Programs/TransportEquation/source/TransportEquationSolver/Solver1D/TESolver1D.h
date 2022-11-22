#include <vector>
#include "TESolver1DOutput.h"
#include "../Instances/VectorField1D.h"
#include "../Methods/Quantity.h"

using namespace std;

template<typename T>
void TESolverStep(Quantity<T> &f,
                  VectorField1D &u,
                  TESolver1DParams &p);

template<typename T>
void SolveTransportEquation1D(Quantity<T> &f,
                              VectorField1D &u,
                              TESolver1DParams &p,
                              TESolver1DOutput &output);
