
#include <functional>
#include <vector>

using namespace std;

double clamp(double x,double lower,double upper);
double minmod(double x,double y);
template<typename T>int sgn(T val);
function<double(double)> linearTransform(const function<double(double)> &f,
                                         double dx, double kx, double dy, double ky);
function<double(double)> fInverseX(const function<double(double)> &f);
function<double(double)> fMoveX(const function<double(double)> &f, double dx);
double errorL2(vector<double> f, const vector<double>& fexact, double h);