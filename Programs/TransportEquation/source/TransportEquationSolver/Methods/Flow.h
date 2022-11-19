//
// Created by grigoriy.senchenok on 18.11.2022.
//

#ifndef TRANSPORTEQUATION_FLOW_H
#define TRANSPORTEQUATION_FLOW_H

#include "TransportVelocity.h"
#include "Quantity.h"

//template<typename Quantity>
class Flow {
public:
    virtual Quantity& calc(Quantity& l, Quantity& r, double dt, TransportVelocity& u) = 0;
};


#endif //TRANSPORTEQUATION_FLOW_H
