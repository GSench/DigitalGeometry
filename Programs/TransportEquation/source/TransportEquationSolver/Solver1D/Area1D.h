#include <vector>
#include <string>
#include <algorithm>

#include "../InterpolationFunctions.h"
#include "Cell1D.h"

using namespace std;

const int CURR = 0;
const int PREV = 0;
const int NEXT = 0;

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
    virtual void movePrev() = 0;
    virtual double get(int offset) = 0;
    virtual F1D getCurrent() = 0;
    virtual void setCurrent(double f) = 0;
    virtual Cell1D getCurrCell(double dx) = 0;
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

    void startIteration() override {
        currentCell = 0;
    }

    bool isFinished() override  {
        return currentCell>=scalarFunction.size();
    }

    void moveNext() override {
        currentCell++;
    }

    void movePrev() override {
        currentCell--;
    }

    double get(int offset) override {
        int i = currentCell+offset;
        return scalarFunction[i%scalarFunction.size()] * (periodicBoundaries || (i>0 && i<scalarFunction.size()));
    }

    F1D getCurrent() override {
        return {get(CURR), get(PREV), get(NEXT)};
    }

    void setCurrent(double f) override {
        scalarFunction[currentCell] = f;
    }

    Cell1D getCurrCell(double dx) override {
        return {(currentCell+0.5)*dx, dx, currentCell*dx, (currentCell+1.0)*dx};
    }

};
