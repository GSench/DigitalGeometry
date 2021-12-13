#include <functional>
#include <vector>

using namespace std;

function<double(double)>PsyGodunov(const vector<double>&f,int i,double beta,double h,double eps);
function<double(double)>PsyTHINCandMUSCL(const vector<double>&f,int i,double beta,double h,double eps);
function<double(double)>PsyTHINCandGodunov(const vector<double>&f,int i,double beta,double h,double eps);
function<double(double)>PsyMUSCL(const vector<double>&f,int i,double beta,double h,double eps);