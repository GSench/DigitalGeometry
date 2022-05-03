//
// Created by gsench on 03.05.22.
//

#ifndef TRANSPORTEQUATION_RBVECTORFIELD1D_H
#define TRANSPORTEQUATION_RBVECTORFIELD1D_H


#include "../../math/MathUtils.h"

class RBVectorField1D {
private:
    double u;
    double uNext;
public:
    RBVectorField1D(double u, double uNext):u(u),uNext(uNext){}

    double getU() const {
        return u;
    }

    double getUNext() const {
        return uNext;
    }

    int direction() const {
        return sgn(u+uNext);
    }
};


#endif //TRANSPORTEQUATION_RBVECTORFIELD1D_H
