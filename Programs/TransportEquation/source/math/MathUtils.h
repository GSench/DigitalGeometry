
#include <functional>

using namespace std;

double clamp(double x,double lower,double upper);
double minmod(double x,double y);
template<typename T>int sgn(T val);
function<double(double)> fInverseX(const function<double(double)> &f);