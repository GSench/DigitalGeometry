#include <cmath>
#include <algorithm>
#include "MathUtils.h"

using namespace std;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

double minmod(double x, double y) {
    if (x * y < 0) return 0;
    else return sgn(x) * min(abs(x), abs(y));
}

double clamp(double x, double lower, double upper) {
    return min(upper, max(x, lower));
}

function<double(double)> linearTransform(const function<double(double)> &f,
                                         double dx, double kx, double dy, double ky){
    return [=](double x)->double {
        return dy + ky * f(dx + kx * x);
    };
}

function<double(double)> fInverseX(const function<double(double)> &f){
    return linearTransform(f, 0, -1, 0, 1);
}

function<double(double)> fMoveX(const function<double(double)> &f, double dx){
    return linearTransform(f, dx, 1, 0, 1);
}