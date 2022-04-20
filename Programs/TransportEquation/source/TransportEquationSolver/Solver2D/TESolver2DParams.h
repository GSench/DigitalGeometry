//
// Created by grigoriy.senchenok on 08.02.2022.
//

#ifndef TRANSPORTEQUATION_TESOLVER2DPARAMS_H
#define TRANSPORTEQUATION_TESOLVER2DPARAMS_H

#include <functional>
#include <string>
#include "../Solver1D/TESolver1DParams.h"

using namespace std;

// TODO refactor class TESolver2DParams
class TESolver2DParams : public TESolver1DParams {
private:
    int cellCountX;
    int cellCountY;
public:

    TESolver2DParams(
            double dx, int cellCountX, int cellCountY,
            double dt, int nTimeSteps,
            const function<function<double(double)>(F1D, C1D)> &flowInterpolationFunction
            ) :
            TESolver1DParams(
                    dx, cellCountX,
                    dt, nTimeSteps,
                    flowInterpolationFunction
                    ),
                    cellCountX(cellCountX),
                    cellCountY(cellCountY)
                    {}

    TESolver2DParams(double CFL, double uPrimary,
                     double areaWidth, double areaHeight, int cellCountX, int nTimeSteps,
                     const function<function<double(double)>(F1D, C1D)> &flowInterpolationFunction
                   ) :
                   TESolver1DParams(CFL, uPrimary,
                                    areaWidth, cellCountX,
                                    nTimeSteps,
                                    flowInterpolationFunction),
                                    cellCountX(cellCountX),
                                    cellCountY((int)(areaHeight/(areaWidth/cellCountX)))
                                    {}

    void projectX(){
        cellCount = cellCountX;
    }
    void projectY(){
        cellCount = cellCountY;
    }

    int getCellCountX() const {
        return cellCountX;
    }

    int getCellCountY() const {
        return cellCountY;
    }
};

#endif //TRANSPORTEQUATION_TESOLVER2DPARAMS_H
