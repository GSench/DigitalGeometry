#ifndef TRANSPORTEQUATION_AREA1D_H
#define TRANSPORTEQUATION_AREA1D_H

#include <vector>
#include "Solver1DInstances.h"

using namespace std;

class Area1D : public LineInterface {
private:
    bool periodicBoundaries = true;
    vector<double> scalarFunction;
public:
    Area1D(bool periodicBoundaries, const vector<double> &scalarFunction):
            periodicBoundaries(periodicBoundaries),
            scalarFunction(scalarFunction) {}

    double operator[](int i) override {
        return scalarFunction[i%scalarFunction.size()] * (periodicBoundaries || (i>=0 || i<scalarFunction.size()));
    }

    void set(int i, double val) override {
        scalarFunction[i] = val;
    }

    int size() override {
        return scalarFunction.size();
    }
};


#endif //TRANSPORTEQUATION_AREA1D_H