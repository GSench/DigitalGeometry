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
    Area1D(int cellCount, bool periodicBoundaries):
            periodicBoundaries(periodicBoundaries),
            scalarFunction(vector<double>(cellCount, 0)) {}

    double operator[](int i) override {
        return scalarFunction[(i+scalarFunction.size())%scalarFunction.size()] * (periodicBoundaries || (i>=0 || i<scalarFunction.size()));
    }

    void set(int i, double val) override {
        scalarFunction[i] = val;
    }

    int size() override {
        return scalarFunction.size();
    }

    vector<double> getF(){
        return scalarFunction;
    }

    void fillRightHalfWith(double val){
        for(int i=scalarFunction.size()/2; i<scalarFunction.size(); i++)
            scalarFunction[i] = val;
    }

    void fillLeftHalfWith(double val){
        for(int i=0; i<scalarFunction.size()/2; i++)
            scalarFunction[i] = val;
    }
    //TODO void drawStruct(double val, int start, int count){}
    //TODO void drawStruct(double val, int start, int end){}

};

#endif //TRANSPORTEQUATION_AREA1D_H