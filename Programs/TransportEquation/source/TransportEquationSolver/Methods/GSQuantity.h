//
// Created by grigoriy.senchenok on 08.12.2022.
//

#ifndef TRANSPORTEQUATION_GSQUANTITY_H
#define TRANSPORTEQUATION_GSQUANTITY_H

#include <cmath>
#include <utility>
#include "../../math/Vector.h"

class GSQuantity {
private:
    Vector gasSolidState;
    double gamma = 1;
public:
    GSQuantity(Vector gasSolidState, double gamma) :
        gasSolidState(std::move(gasSolidState)),
        gamma(gamma)
        {}

    GSQuantity(double volumeFraction, double density, double velocity, double pressure, double gamma):
            gasSolidState({
                volumeFraction,
                volumeFraction*density,
                volumeFraction*density*velocity,
                volumeFraction*density*(pow(velocity,2)/2.+pressure/density/(gamma-1))
            }),
            gamma(gamma)
            {}

    double volumeFraction(){
        return gasSolidState[0];
    }
    double density(){
        return gasSolidState[1] / gasSolidState[0];
    }
    double velocity(){
        return gasSolidState[2] / gasSolidState[1];
    }
    double pressure(){
        return (gasSolidState[3] / gasSolidState[1] - 0.5 * pow(velocity(), 2)) * density() * (gamma - 1);
    }

    Vector getGasSolidState() const {
        return gasSolidState;
    }

    double getGamma() const {
        return gamma;
    }

    // State operations

    GSQuantity operator+(const GSQuantity& q) const {
        return {q.gasSolidState + gasSolidState, gamma};
    }

    void operator+=(const GSQuantity& q) {
        gasSolidState+=q.gasSolidState;
    }

    GSQuantity operator-(const GSQuantity& q) const {
        return {gasSolidState - q.gasSolidState, gamma};
    }


    void operator-=(const GSQuantity& q) {
        gasSolidState-=q.gasSolidState;
    }

    // Scale operations

    GSQuantity operator*(double s) const {
        return {gasSolidState * s, gamma};
    }

    void operator*=(double s) {
        gasSolidState*=s;
    }

    GSQuantity operator/(double s) const {
        return {gasSolidState / s, gamma};
    }

    void operator/=(double s) {
        gasSolidState/=s;
    }
};


#endif //TRANSPORTEQUATION_GSQUANTITY_H
