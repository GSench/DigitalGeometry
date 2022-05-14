//
// Created by gsench on 10.05.22.
//

#ifndef TRANSPORTEQUATION_JRUTILS_H
#define TRANSPORTEQUATION_JRUTILS_H

#include <functional>

double getXiavgJR(double xiRight, double deltaXi, double gamma, double fi, double fiMin, double deltaFi);
std::function<double(double)> FiJR(double gamma, double xiavg);

#endif //TRANSPORTEQUATION_JRUTILS_H
