#include <vector>
#include "Solver1DOutput.h"
#include "Area1D.h"
#include "VectorField1D.h"

using namespace std;

void SolverStep(LineInterface &f,
                LineInterface &u,
                Solver1DParams &p);
void SolveTransportEquation1D(Area1D &f,
                              VectorField1D &u,
                              Solver1DParams &p,
                              Solver1DOutput &output);
double errorL2(vector<double>, const vector<double>&, double);
