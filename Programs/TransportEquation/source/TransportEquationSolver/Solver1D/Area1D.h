#include <vector>
#include <string>
#include <algorithm>

#include "../InterpolationFunctions.h"
#include "Cell1D.h"

using namespace std;

struct F1D {
    double fi;
    double fiPrev;
    double fiNext;
};

class LineInterface {
public:
    virtual ~LineInterface() = default;
    virtual bool hasPeriodicBoundaries() const = 0;
    virtual void startIteration() = 0;
    virtual bool isFinished() = 0;
    virtual void moveNext() = 0;
    virtual void moveToLast() = 0;
    virtual F1D getCurrent() = 0;
    virtual void setCurrent(double f) = 0;
    virtual Cell1D getCurrentCell(double dx) = 0;
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

    bool hasPeriodicBoundaries() const override {
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

    void moveToLast() override {
        currentCell = scalarFunction.size() - 1;
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

    Cell1D getCurrentCell(double dx) override {
        return {(currentCell+0.5)*dx, dx, currentCell*dx, (currentCell+1.0)*dx};
    }

};
