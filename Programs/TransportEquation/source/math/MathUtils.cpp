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