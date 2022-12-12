//
// Created by grigoriy.senchenok on 18.11.2022.
//

#ifndef TRANSPORTEQUATION_OVEREDGEFLOW_H
#define TRANSPORTEQUATION_OVEREDGEFLOW_H

#include "Quantity.h"

template<typename Q, typename F>
class OverEdgeFlow {
public:
    virtual F calc(Quantity<Q>& l, Quantity<Q>& r, double dt) = 0;
};


#endif //TRANSPORTEQUATION_OVEREDGEFLOW_H
