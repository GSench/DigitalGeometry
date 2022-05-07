//
// Created by grigoriy.senchenok on 26.04.2022.
//

#ifndef TRANSPORTEQUATION_DGSOLVER2DPARAMS_H
#define TRANSPORTEQUATION_DGSOLVER2DPARAMS_H

#include <vector>
#include <functional>
#include "../../TransportEquationSolver/Instances/TESolver1DInstances.h"
#include "../../TransportEquationSolver/Solver2D/TESolver2DParams.h"
#include "../../EulerEquationProblem/EESolver2D/EESolver2DParams.h"

using namespace std;

class DGSolver2DParams {
private:
    TESolver2DParams teParams;
    EESolver2DParams eeParams;
public:

    DGSolver2DParams(
            double dx, int cellCountX, int cellCountY,
            double dt, int nTimeSteps,
            const function<function<double(double)>(F1D, C1D)> &flowInterpolationFunction
    ) :
            teParams(dx, cellCountX, cellCountY, dt, nTimeSteps, flowInterpolationFunction),
            eeParams(dt, nTimeSteps)
    {}

    DGSolver2DParams(double CFL, double uPrimary,
                     double areaWidth, double areaHeight, int cellCountX, int nTimeSteps,
                     const function<function<double(double)>(F1D, C1D)> &flowInterpolationFunction
    ) :
            teParams(CFL, uPrimary, areaWidth, areaHeight, cellCountX, nTimeSteps, flowInterpolationFunction),
            eeParams(teParams.getDt(), nTimeSteps)
    {}

    TESolver2DParams& getParamsForTE2D() {
        return teParams;
    }

    EESolver2DParams& getParamsForEE2D() {
        return eeParams;
    }

};


#endif //TRANSPORTEQUATION_DGSOLVER2DPARAMS_H
