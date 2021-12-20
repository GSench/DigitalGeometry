#include <functional>
#include <vector>

using namespace std;

function<double(double)>PsyGodunov(double fi);
function<double(double)>PsyTHINCandMUSCL(double fi, double fiPrev, double fiNext,int i,double beta,double h,double eps);
function<double(double)>PsyTHINCandGodunov(double fi, double fiPrev, double fiNext,int i,double beta,double h,double eps);
function<double(double)>PsyMUSCL(double fi, double fiPrev, double fiNext,int i,double h);