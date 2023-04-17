#include <cmath>
#include <algorithm>
#include <numeric>
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

double ifZero(double val, double caseValIsZero){
    return abs(val) <= 1e-14? (val < 0 ? -caseValIsZero : caseValIsZero) : val;
}

double H(double x){
    return x>=0.0 || x==-0.0? 1 : 0;
}

double H0(double x){
    return x>0.0? 1 : 0;
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

double errorL2(vector<double> f, const vector<double>& fexact, double h){
    double error = 0;
    for (int i = 0; i < f.size(); i++) {
        error += pow(f[i]*h - fexact[i] * h, 2);
    }
    error = sqrt(error);
    return error;
}