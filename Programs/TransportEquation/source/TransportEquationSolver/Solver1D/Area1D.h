#include <vector>
#include <string>
#include <algorithm>

#include "../InterpolationFunctions.h"

using namespace std;

struct Cell1D {
    int i;
    double h;
    double fi;
    double fiPrev;
    double fiNext;
    double xL;
    double xR;
    double uL;
    double uR;
};

class Area1D {
private:
    double dx = 0;

    int cellCount = 20;
    bool periodicBoundaries = true;
    double areaLength = 1;

    function<function<double(double)>(double, double, double, int, double)> FlowInterpolationFunction =
            [=](double fi, double fiPrev, double fiNext, int i, double h)->function<double(double)> {
                return PsyTHINCandMUSCL(fi, fiPrev, fiNext, i,  3.5, h, 1e-4);
            };
    string FlowInterpolationFunctionName = "Psy THINC + MUSCL";

    vector<double> scalarFunction;
    int currentCell = 0;

    double dt = 0;
    double CFL = 0.3;

    function<vector<double>()> vectorField;

public:

    Area1D(double areaLength,
           int cellCount,
           bool periodicBoundaries) :

            cellCount(cellCount),
            periodicBoundaries(periodicBoundaries),
            areaLength(areaLength),
            dx(areaLength/cellCount),
            scalarFunction(cellCount, 0.0),
            currentCell(0)

            {}

    double getDX() const{
        return dx;
    }

    int getCellCount() const {
        return cellCount;
    }

    double getAreaLength() const {
        return areaLength;
    }

    bool hasPeriodicBoundaries() const {
        return periodicBoundaries;
    }

    const function<function<double(double)>(double, double, double, int, double)> &getFlowInterpFunc() const {
        return FlowInterpolationFunction;
    }

    const string &getFlowInterpFuncName() const {
        return FlowInterpolationFunctionName;
    }

    void startIteration(){
        currentCell = 0;
    }

    bool isFinished() const {
        return currentCell>=cellCount;
    }

    void moveNext() {
        currentCell++;
    }

    Cell1D getCurrent(){
        if(currentCell==cellCount-1)
            return {currentCell, dx,
                    scalarFunction[currentCell], scalarFunction[0] * periodicBoundaries, scalarFunction[currentCell+1],
                    currentCell*dx, (currentCell+1)*dx};
        if(currentCell==0)
            return {currentCell, dx,
                    scalarFunction[currentCell], scalarFunction[currentCell-1], scalarFunction[cellCount-1] * periodicBoundaries,
                    currentCell*dx, (currentCell+1)*dx};
        return {currentCell, dx,
                scalarFunction[currentCell], scalarFunction[currentCell-1], scalarFunction[currentCell+1],
                currentCell*dx, (currentCell+1)*dx};
    }

    void setVectorField(const function<vector<double>()> &vf, double setCFL) {
        vectorField = vf;
        CFL = setCFL;
        vector<double> vf0 = vf();
        double uMax = *max_element(vf0.begin(), vf0.end());
        dt = CFL / dx * uMax;
    }
};
