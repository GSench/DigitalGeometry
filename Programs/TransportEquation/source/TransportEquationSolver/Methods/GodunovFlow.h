//
// Created by grigoriy.senchenok on 18.11.2022.
//

#ifndef TRANSPORTEQUATION_GODUNOVFLOW_H
#define TRANSPORTEQUATION_GODUNOVFLOW_H

#include "Flow.h"

template<typename T>
class GodunovFlow : public Flow<T> {
public:
    T calc(Quantity<T>& l, Quantity<T>& r, double dt, Velocity& u) override {
        return u.direction() > 0 ? l.getQuantity() : r.getQuantity();
    }
};

#endif //TRANSPORTEQUATION_GODUNOVFLOW_H
