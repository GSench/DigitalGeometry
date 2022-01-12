//
// Created by grigoriy.senchenok on 12.01.2022.
//

#ifndef TRANSPORTEQUATION_SOLVER1DPARAMS_H
#define TRANSPORTEQUATION_SOLVER1DPARAMS_H

#include <string>
#include "VectorField1D.h"
#include "../InterpolationFunctions.h"

using namespace std;

struct Solver1DParams {
    double CFL = 0.3;
    double dt = 0;
    function<function<double(double)>(double, double, double, int, double)> FlowInterpolationFunction =
            [=](double fi, double fiPrev, double fiNext, int i, double h)->function<double(double)> {
                return PsyTHINCandMUSCL(fi, fiPrev, fiNext, i,  3.5, h, 1e-4);
            };
    string FlowInterpolationFunctionName = "Psy THINC + MUSCL";
};

Solver1DParams getParamsFor(double CFL, double uPrimary, double dx,
                            const function<function<double(double)>(double, double, double, int, double)>& PsyFunc,
                            const string& PsyFuncName);

#endif //TRANSPORTEQUATION_SOLVER1DPARAMS_H
