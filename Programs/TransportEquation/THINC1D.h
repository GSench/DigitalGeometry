#include <vector>

using namespace std;

struct THINC1Dparams;
void THINC1Dtests();
void oldTestCompare();
void debugDifference();
double THINC1D(const THINC1Dparams&p,vector<double>&f,const vector<double>&fexact);
void initF(vector<double>&f,int L,int R);
