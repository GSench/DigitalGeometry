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
    double areaLength = 1.0;
    int cellCount = 20;
    int NTimeSteps = 100;
    double dx = areaLength/cellCount;
    function<function<double(double)>(F1D f, Cell1D c)> FlowInterpolationFunction =
            [=](F1D f, Cell1D c)->function<double(double)> {
                return PsyTHINCandMUSCL(f, c,  3.5, 1e-4);
            };
    string FlowInterpolationFunctionName = "Psy THINC + MUSCL";
};

Solver1DParams getParamsFor(double CFL, double uPrimary, double areaLength, int cellCount,
                            const function<function<double(double)>(double, double, double, int, double)>& PsyFunc,
                            const string& PsyFuncName);

#endif TRANSPORTEQUATION_SOLVER1DPARAMS_H
