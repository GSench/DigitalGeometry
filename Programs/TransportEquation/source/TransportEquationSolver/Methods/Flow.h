//
// Created by grigoriy.senchenok on 18.11.2022.
//

#ifndef TRANSPORTEQUATION_FLOW_H
#define TRANSPORTEQUATION_FLOW_H

#include "TransportVelocity.h"
#include "Quantity.h"

template<typename T>
class Flow {
public:
    virtual T& calc(Quantity<T>& l, Quantity<T>& r, double dt, TransportVelocity& u) = 0;
};


#endif //TRANSPORTEQUATION_FLOW_H
