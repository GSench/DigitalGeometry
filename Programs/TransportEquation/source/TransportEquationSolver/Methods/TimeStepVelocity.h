//
// Created by grigoriy.senchenok on 19.11.2022.
//

#ifndef TRANSPORTEQUATION_TIMESTEPVELOCITY_H
#define TRANSPORTEQUATION_TIMESTEPVELOCITY_H

#include "../../math/MathUtils.h"
#include "Velocity.h"

class TimeStepVelocity : Velocity {
private:
    Vector3D& u;
    Vector3D& uNext;
public:
    TimeStepVelocity(Vector3D& u, Vector3D& uNext) : u(u), uNext(uNext) {}

    Vector3D& getU() const {
        return u;
    }

    Vector3D& getUNext() const {
        return uNext;
    }

    Vector3D direction() override {
        return u+uNext;
    }
};


#endif //TRANSPORTEQUATION_TIMESTEPVELOCITY_H
