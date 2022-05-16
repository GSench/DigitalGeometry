#include <vector>
#include "TESolver1DOutput.h"
#include "../Instances/Area1D.h"
#include "../Instances/VectorField1D.h"
#include "../Instances/RBVectorField1D.h"

using namespace std;

void TERBJRSolverStep(LineInterface &f,
                    RBVectorField1D &u,
                    TESolver1DParams &p);
void SolveTransportEquationRBJR1D(Area1D &f,
                                RBVectorField1D &u,
                                TESolver1DParams &p,
                                TESolver1DOutput &output);