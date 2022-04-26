#include <vector>
#include "TESolver1DOutput.h"
#include "../Instances/Area1D.h"
#include "../Instances/VectorField1D.h"

using namespace std;

void TESolverStep(LineInterface &f,
                  LineInterface &u,
                  TESolver1DParams &p);
void SolveTransportEquation1D(Area1D &f,
                              VectorField1D &u,
                              TESolver1DParams &p,
                              TESolver1DOutput &output);
double errorL2(vector<double>, const vector<double>&, double);
