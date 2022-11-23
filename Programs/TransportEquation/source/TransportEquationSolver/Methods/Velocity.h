//
// Created by grigoriy.senchenok on 18.11.2022.
//

#ifndef TRANSPORTEQUATION_VELOCITY_H
#define TRANSPORTEQUATION_VELOCITY_H

#include <utility>

#include "Quantity.h"

class Velocity : public Quantity<double> {
private:
    Vector3D velocity;
public:
    Velocity(Vector3D& position, const Vector3D& velocity):
        Quantity<double>(position, Vector3D::zero(), velocity.x),
        velocity(velocity)
    {}

    virtual int direction()=0;

    Velocity& prev() override {
        return static_cast<Velocity&>(Quantity<double>::prev());
    }

    Velocity& next() override {
        return static_cast<Velocity&>(Quantity<double>::next());
    }

};


#endif //TRANSPORTEQUATION_VELOCITY_H
