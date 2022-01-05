#include <vector>
#include "Area1D.h"
#include "Solver1DOutput.h"

using namespace std;

void SolveTransportEquation1D(Area1D p, vector<double> &f, const function<vector<double>(int)> &u, Solver1DOutput &output);
double errorL2(vector<double>&, const vector<double>&, double);
void initF(vector<double>&f,int L,int R);
