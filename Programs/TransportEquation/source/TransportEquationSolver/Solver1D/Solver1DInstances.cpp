//
// Created by GSench on 19.01.2022.
//

#include "Solver1DInstances.h"

C1D getCi(const Solver1DParams& p, int i){
    return {(i+0.5)*p.dx, p.dx,i*p.dx,(i+1)*p.dx};
}

F1D getFi(LineInterface& f, int i){
    return {f[i], f[i-1], f[i+1]};
}

U1D getUi(LineInterface& u, int i){
    return {u[i], u[i+1]};
}

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