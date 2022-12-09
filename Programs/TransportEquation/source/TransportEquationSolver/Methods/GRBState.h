//
// Created by grigoriy.senchenok on 08.12.2022.
//

#ifndef TRANSPORTEQUATION_GRBSTATE_H
#define TRANSPORTEQUATION_GRBSTATE_H

#include <cmath>
#include <utility>
#include "../../math/Vector.h"

class GRBState {
private:
    Vector gasRBState;
    double gamma = 1;
public:
    GRBState(Vector gasRbState, double gamma) : gasRBState(std::move(gasRbState)), gamma(gamma) {}

    GRBState(double volumeFraction, double density, double velocity, double pressure, double gamma):
            gasRBState({
                volumeFraction,
                volumeFraction*density,
                volumeFraction*density*velocity,
                volumeFraction*density*(pow(velocity,2)/2.+pressure/density/(gamma-1))
            }),
            gamma(gamma)
            {}

    double volumeFraction(){
        return gasRBState[0];
    }
    double density(){
        return gasRBState[1]/gasRBState[0];
    }
    double velocity(){
        return gasRBState[2]/gasRBState[1];
    }
    double pressure(){
        return (gasRBState[3]/gasRBState[1]-0.5*pow(velocity(), 2))*density()*(gamma-1);
    }

    GRBState operator+(GRBState& q) {
        return {q.gasRBState+gasRBState, gamma};
    }

    void operator+=(GRBState& q) {
        gasRBState+=q.gasRBState;
    }

    GRBState operator-(GRBState& q) const{
        return {gasRBState-q.gasRBState, gamma};
    }

    void operator-=(GRBState& q) {
        gasRBState-=q.gasRBState;
    }

    GRBState operator*(double s) const{
        return {gasRBState*s, gamma};
    }

    void operator*=(double s) {
        gasRBState*=s;
    }

    GRBState operator/(double s) const{
        return {gasRBState/s, gamma};
    }

    void operator/=(double s) {
        gasRBState/=s;
    }
};


#endif //TRANSPORTEQUATION_GRBSTATE_H
