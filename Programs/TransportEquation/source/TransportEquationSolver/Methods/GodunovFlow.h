//
// Created by grigoriy.senchenok on 18.11.2022.
//

#ifndef TRANSPORTEQUATION_GODUNOVFLOW_H
#define TRANSPORTEQUATION_GODUNOVFLOW_H

#include "Flow.h"

template<typename T>
class GodunovFlow : public Flow<T, Velocity&> {
public:
    T calc(Quantity<T>& l, Quantity<T>& r, double dt, Quantity<Velocity&>& u) override {
        return dt/2. * (u.getQuantity().direction()[u.getDirection()] > 0 ? l.getQuantity() : r.getQuantity());
    }
};

#endif //TRANSPORTEQUATION_GODUNOVFLOW_H
