//
// Created by grigoriy.senchenok on 20.04.2022.
//

#ifndef TRANSPORTEQUATION_TESOLVER1DPARAMS_H
#define TRANSPORTEQUATION_TESOLVER1DPARAMS_H

#include "../Methods/OverEdgeFlow.h"

template<typename Q>
class TESolver1DParams {
private:
    double dx;
    double dt;
    int NTimeSteps;

protected:
    int cellCount;
public:

    TESolver1DParams(
            double dx, int cellCount,
            double dt, int nTimeSteps
            ) :
            dx(dx),
            cellCount(cellCount),
            dt(dt),
            NTimeSteps(nTimeSteps)
            {}

    TESolver1DParams(
            double CFL, double uPrimary,
            double areaLength, int cellCount, int nTimeSteps
            ) :
            dx(areaLength/cellCount),
            cellCount(cellCount),
            dt(CFL *  /*dx=*/areaLength/cellCount  / uPrimary),
            NTimeSteps(nTimeSteps)
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

};


#endif //TRANSPORTEQUATION_TESOLVER1DPARAMS_H
