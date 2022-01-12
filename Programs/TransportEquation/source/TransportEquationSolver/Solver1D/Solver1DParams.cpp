//
// Created by grigoriy.senchenok on 12.01.2022.
//

#include "Solver1DParams.h"
#include "VectorField1D.h"

Solver1DParams getParamsFor(double CFL, double uPrimary, double areaLength, int cellCount,
                            const function<function<double(double)>(double, double, double, int, double)>& PsyFunc,
                            const string& PsyFuncName){
    Solver1DParams params;
    params.CFL = CFL;
    params.cellCount = cellCount;
    params.areaLength = areaLength;
    params.dx = areaLength/cellCount;
    params.dt = CFL / params.dx * uPrimary;
    params.FlowInterpolationFunction = PsyFunc;
    params.FlowInterpolationFunctionName = PsyFuncName;
    return params;
}
