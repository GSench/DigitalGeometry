//
// Created by grigoriy.senchenok on 19.11.2022.
//

#ifndef TRANSPORTEQUATION_TIMESTEPVELOCITY_H
#define TRANSPORTEQUATION_TIMESTEPVELOCITY_H

#include <utility>

#include "../../math/Vector.h"

class TimeStepVelocity {
private:
    Vector u;
    Vector uNext;
public:
    TimeStepVelocity(Vector u, Vector uNext) :
        u(std::move(u)),
        uNext(std::move(uNext))
        {}

    Vector& getU() {
        return u;
    }

    Vector& getUNext() {
        return uNext;
    }

    Vector direction() {
        return u+uNext;
    }
};


#endif //TRANSPORTEQUATION_TIMESTEPVELOCITY_H
