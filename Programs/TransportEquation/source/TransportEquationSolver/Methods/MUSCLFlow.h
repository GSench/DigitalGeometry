//
// Created by grigoriy.senchenok on 18.11.2022.
//

#ifndef TRANSPORTEQUATION_MUSCLFLOW_H
#define TRANSPORTEQUATION_MUSCLFLOW_H


#include "Flow.h"
#include "VolumeFraction.h"
#include "TimeTransportVelocity.h"

class MUSCLFlow : Flow {
public:
    Quantity& calc(Quantity& l, Quantity& r, double dt, TransportVelocity& u) override {
        VolumeFraction& fl = dynamic_cast<VolumeFraction&>(l);
        VolumeFraction& fr = dynamic_cast<VolumeFraction&>(r);
        TimeTransportVelocity& ut = dynamic_cast<TimeTransportVelocity&>(u);

        return u.direction() > 0 ? l : r;
    }
};


#endif //TRANSPORTEQUATION_MUSCLFLOW_H
