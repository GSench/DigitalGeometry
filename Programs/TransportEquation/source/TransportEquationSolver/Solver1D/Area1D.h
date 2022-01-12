#include <vector>
#include <string>
#include <algorithm>

#include "../InterpolationFunctions.h"

using namespace std;

struct F1D {
    double dx;
    double fi;
    double fiPrev;
    double fiNext;
    double xL;
    double xR;
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
    double dx = 0;
    int cellCount = 100;
    bool periodicBoundaries = true;

    vector<double> scalarFunction;
    int currentCell = 0;

public:

    Area1D(double areaLength,
           int cellCount,
           bool periodicBoundaries) :

            cellCount(cellCount),
            periodicBoundaries(periodicBoundaries),
            dx(areaLength/cellCount),
            scalarFunction(cellCount, 0.0),
            currentCell(0) {}

    Area1D(int cellCount,
           double dx,
           bool periodicBoundaries) :

            cellCount(cellCount),
            periodicBoundaries(periodicBoundaries),
            dx(dx),
            scalarFunction(cellCount, 0.0),
            currentCell(0) {}

    double getDX() const{
        return dx;
    }

    int getCellCount() const {
        return cellCount;
    }

    bool hasPeriodicBoundaries() const {
        return periodicBoundaries;
    }

    void startIteration() override {
        currentCell = 0;
    }

    bool isFinished() override  {
        return currentCell>=cellCount;
    }

    void moveNext() override {
        currentCell++;
    }

    F1D getCurrent() override {
        if(currentCell==cellCount-1)
            return { dx,
                    scalarFunction[currentCell], scalarFunction[0] * periodicBoundaries, scalarFunction[currentCell+1],
                    currentCell*dx, (currentCell+1)*dx};
        if(currentCell==0)
            return { dx,
                    scalarFunction[currentCell], scalarFunction[currentCell-1], scalarFunction[cellCount-1] * periodicBoundaries,
                    currentCell*dx, (currentCell+1)*dx};
        return { dx,
                scalarFunction[currentCell], scalarFunction[currentCell-1], scalarFunction[currentCell+1],
                currentCell*dx, (currentCell+1)*dx};
    }

    void setCurrent(double f) override {
        scalarFunction[currentCell] = f;
    }

};
