//
// Created by GSench on 20.01.2022.
//

#ifndef TRANSPORTEQUATION_VECTORFIELD1D_H
#define TRANSPORTEQUATION_VECTORFIELD1D_H


#include <utility>

#include "TESolver1DInstances.h"

class VectorField1D: public LineInterface {
private:
    vector<double> u;
    int areaLength;
public:
    explicit VectorField1D(int areaLength): u(areaLength, 0), areaLength(areaLength) {}
    VectorField1D(const vector<double> &u, int areaLength): u(u), areaLength(areaLength) {}

    double operator[](int i) override {
        return u[i];
    }

    void set(int i, double val) override {
        u[i] = val;
    }

    int size() override {
        return areaLength;
    }
};

VectorField1D getStaticVF1D(double uStatic, int size);

#endif //TRANSPORTEQUATION_VECTORFIELD1D_H
