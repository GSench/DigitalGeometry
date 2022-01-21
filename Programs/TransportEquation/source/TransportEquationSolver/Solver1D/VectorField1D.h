//
// Created by GSench on 20.01.2022.
//

#ifndef TRANSPORTEQUATION_VECTORFIELD1D_H
#define TRANSPORTEQUATION_VECTORFIELD1D_H


#include "Solver1DInstances.h"

class VectorField1D: public LineInterface {
private:
    function<double(int)> u;
    int areaLength;
public:
    VectorField1D(const function<double(int)> &u, int areaLength): u(u), areaLength(areaLength) {}

    double operator[](int i) override {
        return u(i);
    }

    void set(int i, double val) override {

    }

    int size() override {
        return areaLength;
    }
};

VectorField1D getStaticVF1D(double uStatic, int size);

#endif //TRANSPORTEQUATION_VECTORFIELD1D_H
