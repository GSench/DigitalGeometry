//
// Created by grigoriy.senchenok on 08.12.2022.
//

#ifndef TRANSPORTEQUATION_GSQUANTITY_H
#define TRANSPORTEQUATION_GSQUANTITY_H

#include <cmath>
#include <utility>
#include <string>
#include "../../math/Vector.h"
#include "../../math/MathUtils.h"

class GSQuantity {
private:
    Vector gasSolidState;
    double solidVelocity;
    double gamma = 1.4;
public:
    GSQuantity(Vector gasSolidState, double gamma, double solidVelocity) :
        gasSolidState(std::move(gasSolidState)),
        gamma(gamma),
        solidVelocity(solidVelocity)
        {}

    GSQuantity(double volumeFraction, double density, double velocity, double pressure, double gamma, double solidVelocity):
            gasSolidState({
                volumeFraction,
                volumeFraction*density,
                volumeFraction*density*velocity,
                volumeFraction*density*(velocity*velocity/2.+pressure/ifZero(density, 1e-10)/(gamma-1))
            }),
            gamma(gamma),
            solidVelocity(solidVelocity)
    {}

    double volumeFraction() const {
        return gasSolidState[0];
    }
    void applyVolumeFraction(double volumeFraction){
        if(gasSolidState[0]==0.0 || gasSolidState[0]==-0.0) gasSolidState*=0.0;
        else gasSolidState = gasSolidState/gasSolidState[0]*volumeFraction;
    }
    double density() const {
        return gasSolidState[0] < 1e-10 ? 0 : gasSolidState[1] / gasSolidState[0];
    }
    double velocity() const {
        return gasSolidState[1] < 1e-10 ? 0 : gasSolidState[2] / gasSolidState[1];
    }
    double pressure() const {
        return gasSolidState[1] < 1e-10 ? 0 :
               (gasSolidState[3] / gasSolidState[1] - 0.5 * pow(velocity(), 2)) * density() * (gamma - 1);
    }

    double energy() const {
        return gasSolidState[1] < 1e-10 ? 0 : gasSolidState[3] / gasSolidState[1];
    }

    bool isSolid(double eps) const {
        return abs(gasSolidState[0]) < eps;
    }

    bool isGas(double eps) const {
        return abs(gasSolidState[0]-1.0) < eps;
    }

    bool isDiscontinuous(double eps) const {
        return !isGas(eps) && !isSolid(eps);
    }

    void inverse() {
        gasSolidState = Vector({gasSolidState[0], gasSolidState[1], -gasSolidState[2], gasSolidState[3]});
        solidVelocity = -solidVelocity;
    }

    Vector getGasSolidState() const {
        return gasSolidState;
    }

    double getGamma() const {
        return gamma;
    }

    double getSolidVelocity() const {
        return solidVelocity;
    }

    void setSolidVelocity(double vs) {
        solidVelocity = vs;
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

    string toString() const {
        return "{("
               + to_string(gasSolidState[0]) + ","
               + to_string(gasSolidState[1]) + ","
               + to_string(gasSolidState[2]) + ","
               + to_string(gasSolidState[3]) + ","
               + ")"
               + ", vs: " + to_string(solidVelocity)
               +'}';
    }
};


#endif //TRANSPORTEQUATION_GSQUANTITY_H
