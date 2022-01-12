#include <vector>
#include <string>
#include <algorithm>

#include "../InterpolationFunctions.h"

using namespace std;

struct F1D {
    double fi;
    double fiPrev;
    double fiNext;
};

class LineInterface {
public:
    virtual ~LineInterface() = default;
    virtual void startIteration() = 0;
    virtual bool isFinished() = 0;
    virtual void moveNext() = 0;
    virtual F1D getCurrent() = 0;
    virtual void setCurrent(double f) = 0;
};

class Area1D: public LineInterface {
private:
    bool periodicBoundaries = true;
    vector<double> scalarFunction;
    int currentCell = 0;

public:

    Area1D(double areaLength,
           int cellCount,
           bool periodicBoundaries) :
            periodicBoundaries(periodicBoundaries),
            scalarFunction(cellCount, 0.0),
            currentCell(0) {}

    Area1D(int cellCount,
           double dx,
           bool periodicBoundaries) :
            periodicBoundaries(periodicBoundaries),
            scalarFunction(cellCount, 0.0),
            currentCell(0) {}

    bool hasPeriodicBoundaries() const {
        return periodicBoundaries;
    }

    void startIteration() override {
        currentCell = 0;
    }

    bool isFinished() override  {
        return currentCell>=scalarFunction.size();
    }

    void moveNext() override {
        currentCell++;
    }

    F1D getCurrent() override {
        if(currentCell==scalarFunction.size()-1)
            return {scalarFunction[currentCell],
                    scalarFunction[0] * periodicBoundaries,
                    scalarFunction[currentCell+1]};
        if(currentCell==0)
            return {scalarFunction[currentCell],
                    scalarFunction[currentCell-1],
                    scalarFunction[scalarFunction.size()-1] * periodicBoundaries};
        return {scalarFunction[currentCell],
                scalarFunction[currentCell-1],
                scalarFunction[currentCell+1]};
    }

    void setCurrent(double f) override {
        scalarFunction[currentCell] = f;
    }

};
