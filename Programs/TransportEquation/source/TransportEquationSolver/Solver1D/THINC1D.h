#include <vector>
#include "THINC1DparamsStruct.h"
#include "Solver1DOutput.h"

using namespace std;

void THINC1D(const THINC1Dparams&, vector<double>&, Solver1DOutput&);
double errorL2(vector<double>&, const vector<double>&, double);
void initF(vector<double>&f,int L,int R);
