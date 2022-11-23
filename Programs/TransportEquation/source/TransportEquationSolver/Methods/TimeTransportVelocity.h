//
// Created by grigoriy.senchenok on 19.11.2022.
//

#ifndef TRANSPORTEQUATION_TIMETRANSPORTVELOCITY_H
#define TRANSPORTEQUATION_TIMETRANSPORTVELOCITY_H

#include "../../math/MathUtils.h"
#include "Velocity.h"

class TimeTransportVelocity : Velocity {
private:
    double u = 0;
    double uNext = 0;
public:
    TimeTransportVelocity(double u, double uNext) : u(u), uNext(uNext) {}

    double getU() const {
        return u;
    }

    double getUNext() const {
        return uNext;
    }

    int direction() override {
        return sgn(u + uNext);
    }
};


#endif //TRANSPORTEQUATION_TIMETRANSPORTVELOCITY_H
