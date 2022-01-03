#include <vector>
#include "Solver1DParamsStruct.h"
#include "Solver1DOutput.h"

using namespace std;

void SolveTransportEquation1D(const Solver1DParams &p, vector<double> &f, Solver1DOutput &output);
double errorL2(vector<double>&, const vector<double>&, double);
void initF(vector<double>&f,int L,int R);
