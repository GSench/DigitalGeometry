//
// Created by grigoriy.senchenok on 20.04.2022.
//

#ifndef TRANSPORTEQUATION_TESOLVER1DPARAMS_H
#define TRANSPORTEQUATION_TESOLVER1DPARAMS_H

#include "../Instances/TESolver1DInstances.h"
#include "../Methods/Flow.h"

class TESolver1DParams {
private:
    double dx;
    double dt;
    int NTimeSteps;
    Flow& flow;

protected:
    int cellCount;
public:

    TESolver1DParams(
            double dx, int cellCount,
            double dt, int nTimeSteps,
            Flow& flow
            ) :
            dx(dx),
            cellCount(cellCount),
            dt(dt),
            NTimeSteps(nTimeSteps),
            flow(flow)
            {}

    TESolver1DParams(
            double CFL, double uPrimary,
            double areaLength, int cellCount, int nTimeSteps,
            Flow& flow
            ) :
            dx(areaLength/cellCount),
            cellCount(cellCount),
            dt(CFL *  /*dx=*/areaLength/cellCount  / uPrimary),
            NTimeSteps(nTimeSteps),
            flow(flow)
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

    Flow& getFlow() {
        return flow;
    }
};


#endif //TRANSPORTEQUATION_TESOLVER1DPARAMS_H
