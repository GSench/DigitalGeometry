//
// Created by grigoriy.senchenok on 08.02.2022.
//

#ifndef TRANSPORTEQUATION_SOLVER2DINSTANCES_H
#define TRANSPORTEQUATION_SOLVER2DINSTANCES_H

#include <functional>
#include <string>
#include "../Solver1D/Solver1DInstances.h"

using namespace std;

// TODO refactor class Solver2DParams
class Solver2DParams : public Solver1DParams {
public:
    double areaWidth;
    double areaHeight;
    int cellCountX;
    int cellCountY;
    void projectX(){
        areaLength = areaWidth;
        cellCount = cellCountX;
    }
    void projectY(){
        areaLength = areaHeight;
        cellCount = cellCountY;
    }
};

Solver2DParams get2DParamsFor(double CFL, double uPrimary,
                              double areaWidth, double areaHeight, int cellCountX,
                              int NTimeSteps,
                              const function<function<double(double)>(F1D f, C1D c)>& PsyFunc,
                              const string& PsyFuncName);


#endif //TRANSPORTEQUATION_SOLVER2DINSTANCES_H
