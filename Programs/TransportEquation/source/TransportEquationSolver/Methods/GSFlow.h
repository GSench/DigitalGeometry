//
// Created by grigoriy.senchenok on 08.12.2022.
//

#ifndef TRANSPORTEQUATION_GSFLOW_H
#define TRANSPORTEQUATION_GSFLOW_H

#include <cmath>
#include <utility>
#include "../../math/Vector.h"
#include "GSQuantity.h"

class GSFlow {
private:
    Vector gasSolidState;
    double gamma = 1;
public:
    GSFlow(Vector gasSolidState, double gamma) : gasSolidState(std::move(gasSolidState)), gamma(gamma) {}

    GSFlow(double volumeFraction, double density, double velocity, double pressure, double gamma):
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

    // Flow operations

    GSFlow operator+(const GSFlow& q) const {
        return {q.getGasSolidState() + gasSolidState, gamma};
    }

    void operator+=(const GSFlow& q) {
        gasSolidState+=q.getGasSolidState();
    }

    GSFlow operator-(const GSFlow& q) const {
        return {gasSolidState - q.getGasSolidState(), gamma};
    }

    void operator-=(const GSFlow& q) {
        gasSolidState-=q.getGasSolidState();
    }

    // State operations


    GSQuantity operator+(const GSQuantity& q) const {
        return {gasSolidState+q.getGasSolidState(), gamma};
    }

    GSQuantity friend operator+(const GSQuantity& q, const GSFlow& f) {
        return {q.getGasSolidState()+f.getGasSolidState(), q.getGamma()};
    }

    GSQuantity operator-(const GSQuantity& q) const {
        return {gasSolidState-q.getGasSolidState(), gamma};
    }

    GSQuantity friend operator-(const GSQuantity& q, const GSFlow& f) {
        return {q.getGasSolidState()-f.getGasSolidState(), q.getGamma()};
    }

    // Scale operations

    GSFlow operator*(double s) const {
        return {gasSolidState * s, gamma};
    }

    void operator*=(double s) {
        gasSolidState*=s;
    }

    GSFlow operator/(double s) const {
        return {gasSolidState / s, gamma};
    }

    void operator/=(double s) {
        gasSolidState/=s;
    }
};


#endif //TRANSPORTEQUATION_GSFLOW_H
