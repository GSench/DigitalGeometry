//
// Created by grigoriy.senchenok on 18.11.2022.
//

#ifndef TRANSPORTEQUATION_MUSCLFLOW_H
#define TRANSPORTEQUATION_MUSCLFLOW_H


#include "Flow.h"
#include "TimeStepVelocity.h"

class MUSCLFlow : Flow<double, TimeStepVelocity&> {
public:
    double calc(Quantity<double>& l, Quantity<double>& r, double dt, Quantity<TimeStepVelocity&>& u) override {
        double transportSpeed = u.getQuantity().getU()[u.getDirection()];
        return transportSpeed > 0 ? l.getQuantity() : r.getQuantity();
    }
};


#endif //TRANSPORTEQUATION_MUSCLFLOW_H
