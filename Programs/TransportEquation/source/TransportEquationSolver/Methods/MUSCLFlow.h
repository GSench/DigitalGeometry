//
// Created by grigoriy.senchenok on 18.11.2022.
//

#ifndef TRANSPORTEQUATION_MUSCLFLOW_H
#define TRANSPORTEQUATION_MUSCLFLOW_H


#include "Flow.h"
#include "TimeTransportVelocity.h"

class MUSCLFlow : Flow<double> {
public:
    double calc(Quantity<double>& l, Quantity<double>& r, double dt, Velocity& u) override {
        return u.direction() > 0 ? l.getQuantity() : r.getQuantity();
    }
};


#endif //TRANSPORTEQUATION_MUSCLFLOW_H
