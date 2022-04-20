//
// Created by grigoriy.senchenok on 20.04.2022.
//

#ifndef TRANSPORTEQUATION_TESOLVER1DPARAMS_H
#define TRANSPORTEQUATION_TESOLVER1DPARAMS_H

#include "Solver1DInstances.h"

class TESolver1DParams {
private:
    double dx;
    double dt;
    int NTimeSteps;
    function<function<double(double)>(F1D f, C1D c)> FlowInterpolationFunction;

protected:
    int cellCount;
public:

    TESolver1DParams(
            double dx, int cellCount,
            double dt, int nTimeSteps,
            const function<function<double(double)>(F1D, C1D)> &flowInterpolationFunction
            ) :
            dx(dx),
            cellCount(cellCount),
            dt(dt),
            NTimeSteps(nTimeSteps),
            FlowInterpolationFunction(flowInterpolationFunction)
            {}

    TESolver1DParams(
            double CFL, double uPrimary,
            double areaLength, int cellCount, int nTimeSteps,
            const function<function<double(double)>(F1D, C1D)> &flowInterpolationFunction
            ) :
            dx(areaLength/cellCount),
            cellCount(cellCount),
            dt(CFL *  /*dx=*/areaLength/cellCount  / uPrimary),
            NTimeSteps(nTimeSteps),
            FlowInterpolationFunction(flowInterpolationFunction)
    {}
    double getDx() const {
        return dx;
    }

    int getCellCount() const {
        return cellCount;
    }

    double getDt() const {
        return dt;
    }

    int getNTimeSteps() const {
        return NTimeSteps;
    }

    const function<function<double(double)>(F1D, C1D)> &getFlowInterpolationFunctionFabric() const {
        return FlowInterpolationFunction;
    }
};


#endif //TRANSPORTEQUATION_TESOLVER1DPARAMS_H
