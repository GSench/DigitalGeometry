//
// Created by grigoriy.senchenok on 18.11.2022.
//

#ifndef TRANSPORTEQUATION_GODUNOVFLOW_H
#define TRANSPORTEQUATION_GODUNOVFLOW_H

#include "Flow.h"
#include "VolumeFraction.h"

class GodunovFlow : public Flow {
public:
    Quantity& calc(Quantity& l, Quantity& r, double dt, TransportVelocity& u) override {
        return u.direction() > 0 ? l : r;
    }
};

#endif //TRANSPORTEQUATION_GODUNOVFLOW_H
