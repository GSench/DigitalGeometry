//
// Created by grigoriy.senchenok on 08.02.2022.
//

#include "Solver2DInstances.h"

Solver2DParams get2DParamsFor(double CFL, double uPrimary,
                              double areaWidth, double areaHeight, int cellCountX,
                              int NTimeSteps,
                              const function<function<double(double)>(F1D f, C1D c)>& PsyFunc,
                              const string& PsyFuncName){

    Solver2DParams params;

    params.areaWidth = areaWidth;
    params.cellCountX = cellCountX;
    params.dx = areaWidth/cellCountX;
    params.cellCountY = (int) (areaHeight/params.dx);
    params.areaHeight = params.cellCountY * params.dx;

    params.CFL = CFL;
    params.NTimeSteps = NTimeSteps;
    params.dt = CFL * params.dx / uPrimary;

    params.FlowInterpolationFunction = PsyFunc;
    params.FlowInterpolationFunctionName = PsyFuncName;

    return params;
}