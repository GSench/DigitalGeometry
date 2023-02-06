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
    Vector solidVelocity;
    double gamma = 1.4;
public:
    GSQuantity(Vector gasSolidState, double gamma, Vector solidVelocity) :
        gasSolidState(std::move(gasSolidState)),
        gamma(gamma),
        solidVelocity(std::move(solidVelocity))
        {}

    GSQuantity(double volumeFraction, double density, double velocity, double pressure, double gamma, Vector solidVelocity):
            gasSolidState({
                volumeFraction,
                volumeFraction*density,
                volumeFraction*density*velocity,
                volumeFraction*density*(pow(velocity,2)/2.+pressure/density/(gamma-1))
            }),
            gamma(gamma),
            solidVelocity(std::move(solidVelocity))
    {}

    double volumeFraction() const {
        return gasSolidState[0];
    }
    double density() const {
        return gasSolidState[1] / gasSolidState[0];
    }
    double velocity() const {
        return gasSolidState[2] / gasSolidState[1];
    }
    double pressure() const {
        return (gasSolidState[3] / gasSolidState[1] - 0.5 * pow(velocity(), 2)) * density() * (gamma - 1);
    }

    Vector getGasSolidState() const {
        return gasSolidState;
    }

    double getGamma() const {
        return gamma;
    }

    Vector getSolidVelocity() const {
        return solidVelocity;
    }

    double soundSpeed() const {
        return sqrt(gamma*pressure()/density());
    }

    // State operations

    GSQuantity operator+(const GSQuantity& q) const {
        return {q.gasSolidState + gasSolidState, gamma, solidVelocity};
    }

    void operator+=(const GSQuantity& q) {
        gasSolidState+=q.gasSolidState;
    }

    GSQuantity operator-(const GSQuantity& q) const {
        return {gasSolidState - q.gasSolidState, gamma, solidVelocity};
    }


    void operator-=(const GSQuantity& q) {
        gasSolidState-=q.gasSolidState;
    }

    // Scale operations

    GSQuantity operator*(double s) const {
        return {gasSolidState * s, gamma, solidVelocity};
    }

    GSQuantity friend operator*(double s, const GSQuantity& q) {
        return {q.gasSolidState * s, q.gamma, q.solidVelocity};
    }

    void operator*=(double s) {
        gasSolidState*=s;
    }

    GSQuantity operator/(double s) const {
        return {gasSolidState / s, gamma, solidVelocity};
    }

    GSQuantity friend operator/(double s, const GSQuantity& q) {
        return {q.gasSolidState / s, q.gamma, q.solidVelocity};
    }

    void operator/=(double s) {
        gasSolidState/=s;
    }
};


#endif //TRANSPORTEQUATION_GSQUANTITY_H
