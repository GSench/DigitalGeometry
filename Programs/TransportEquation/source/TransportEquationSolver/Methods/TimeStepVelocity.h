//
// Created by grigoriy.senchenok on 19.11.2022.
//

#ifndef TRANSPORTEQUATION_TIMESTEPVELOCITY_H
#define TRANSPORTEQUATION_TIMESTEPVELOCITY_H

#include "../../math/MathUtils.h"
#include "../../math/Vector.h"

class TimeStepVelocity {
private:
    Vector& u;
    Vector& uNext;
public:
    TimeStepVelocity(Vector& u, Vector& uNext) : u(u), uNext(uNext) {}

    Vector& getU() const {
        return u;
    }

    Vector& getUNext() const {
        return uNext;
    }

    Vector direction() {
        return u+uNext;
    }
};


#endif //TRANSPORTEQUATION_TIMESTEPVELOCITY_H
