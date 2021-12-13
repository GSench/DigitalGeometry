#include <vector>
#include "THINC1DparamsStruct.h"

using namespace std;

double THINC1D(const THINC1Dparams&p,vector<double>&f,const vector<double>&fexact);
void initF(vector<double>&f,int L,int R);
