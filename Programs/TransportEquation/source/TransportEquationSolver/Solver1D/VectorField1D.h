//
// Created by grigoriy.senchenok on 12.01.2022.
//

#ifndef TRANSPORTEQUATION_VECTORFIELD1D_H
#define TRANSPORTEQUATION_VECTORFIELD1D_H

#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

struct U1D {
    double uL;
    double uR;
};

class ULineInterface {
public:
    virtual ~ULineInterface() = default;
    virtual void startIteration() = 0;
    virtual bool isFinished() = 0;
    virtual void moveNext() = 0;
    virtual U1D getCurrent() = 0;
    virtual void setCurrent(double ui) = 0;
    virtual double getUPrimary() = 0;
    virtual Cell1D getCurrentCell(double dx) = 0;
};

class VectorField1D : ULineInterface {

private:

    vector<double> u;
    int currentCell = 0;

public:

    VectorField1D(double dx,
                  int cellCount,
                  const vector<double> &u) :
                  u(u) {}

    void startIteration() override {
        currentCell = 0;
    }
    bool isFinished() override {
        return currentCell>=u.size();
    }
    void moveNext() override {
        currentCell++;
    }
    U1D getCurrent() override {
        return {u[currentCell], u[currentCell+1]};
    }
    void setCurrent(double ui) override {
        u[currentCell] = ui;
    }
    double getUPrimary() override {
        return *max_element(u.begin(), u.end());
    }
    Cell1D getCurrentCell(double dx) override {
        return {(currentCell+0.5)*dx, dx, currentCell*dx, (currentCell+1.0)*dx};
    }
};


#endif //TRANSPORTEQUATION_VECTORFIELD1D_H
