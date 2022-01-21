#include <vector>
#include "Solver1DOutput.h"

using namespace std;

void SolverStep(LineInterface &f,
                LineInterface &u,
                Solver1DParams &p);
void SolveTransportEquation1D(LineInterface &f,
                              LineInterface &u,
                              Solver1DParams &p,
                              Solver1DOutput &output);
double errorL2(vector<double>, const vector<double>&, double);
void initF(vector<double>&f,int L,int R);
