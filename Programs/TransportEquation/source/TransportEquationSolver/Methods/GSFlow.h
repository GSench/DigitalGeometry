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
    Vector solidVelocity;
public:
    GSFlow(Vector gasSolidState, double gamma, Vector solidVelocity) :
        gasSolidState(std::move(gasSolidState)),
        gamma(gamma),
        solidVelocity(std::move(solidVelocity))
    {}

    GSFlow(double volumeFraction, double density, double velocity, double pressure, double gamma, Vector solidVelocity):
            gasSolidState({
                volumeFraction*solidVelocity[0], //TODO 1D stub
                volumeFraction*density*velocity,
                volumeFraction*density*velocity*velocity + pressure,
                volumeFraction*density*(pow(velocity,2)/2.+pressure/density/(gamma-1)+pressure/density)
            }),
            gamma(gamma),
            solidVelocity(std::move(solidVelocity))
    {}

    explicit GSFlow(const GSQuantity& q):
            GSFlow(q.volumeFraction(),
                   q.density(),
                   q.velocity(),
                   q.pressure(),
                   q.getGamma(),
                   q.getSolidVelocity())
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

    Vector getSolidVelocity() const {
        return solidVelocity;
    }

    // Flow operations

    GSFlow operator+(const GSFlow& f) const {
        return {f.getGasSolidState() + gasSolidState, gamma, solidVelocity};
    }

    void operator+=(const GSFlow& f) {
        gasSolidState+=f.getGasSolidState();
    }

    GSFlow operator-(const GSFlow& f) const {
        return {gasSolidState - f.getGasSolidState(), gamma, solidVelocity};
    }

    void operator-=(const GSFlow& f) {
        gasSolidState-=f.getGasSolidState();
    }

    // State operations


    GSQuantity operator+(const GSQuantity& q) const {
        return {gasSolidState+q.getGasSolidState(), gamma, q.getSolidVelocity()};
    }

    GSQuantity friend operator+(const GSQuantity& q, const GSFlow& f) {
        return {q.getGasSolidState()+f.getGasSolidState(), q.getGamma(), q.getSolidVelocity()};
    }

    GSQuantity operator-(const GSQuantity& q) const {
        return {gasSolidState-q.getGasSolidState(), gamma, q.getSolidVelocity()};
    }

    GSQuantity friend operator-(const GSQuantity& q, const GSFlow& f) {
        return {q.getGasSolidState()-f.getGasSolidState(), q.getGamma(), q.getSolidVelocity()};
    }

    // Scale operations

    GSFlow operator*(double s) const {
        return {gasSolidState * s, gamma, solidVelocity};
    }

    GSFlow friend operator*(double s, const GSFlow& f) {
        return {f.gasSolidState * s, f.gamma, f.solidVelocity};
    }

    void operator*=(double s) {
        gasSolidState*=s;
    }

    GSFlow operator/(double s) const {
        return {gasSolidState / s, gamma, solidVelocity};
    }

    GSFlow friend operator/(double s, const GSFlow& f) {
        return {f.gasSolidState / s, f.gamma, f.solidVelocity};
    }

    void operator/=(double s) {
        gasSolidState/=s;
    }
};

inline GSFlow convertQuantity(const GSQuantity& q){
    return {q.getGasSolidState(), q.getGamma(), q.getSolidVelocity()};
}

#endif //TRANSPORTEQUATION_GSFLOW_H
