//
// Created by grigoriy.senchenok on 08.12.2022.
//

#ifndef TRANSPORTEQUATION_GSFLOW_H
#define TRANSPORTEQUATION_GSFLOW_H

#include <cmath>
#include <utility>
#include <string>
#include "../../math/Vector.h"
#include "GSQuantity.h"

using namespace std;

class GSFlow {
private:
    Vector gasSolidState;
    double gamma = 1;
    double solidVelocity;
public:
    GSFlow(Vector gasSolidState, double gamma, double solidVelocity) :
        gasSolidState(std::move(gasSolidState)),
        gamma(gamma),
        solidVelocity(solidVelocity)
    {}

    GSFlow(double volumeFraction, double density, double velocity, double pressure, double gamma, double solidVelocity):
            gasSolidState({
                volumeFraction*solidVelocity,
                volumeFraction*density*velocity,
                volumeFraction*(density*velocity*velocity + pressure),
                volumeFraction*density*velocity*(velocity*velocity/2.+pressure/ifZero(density, 1e-10)/(gamma-1)+pressure/ifZero(density, 1e-10))
            }),
            gamma(gamma),
            solidVelocity(solidVelocity)
    {}

    explicit GSFlow(const GSQuantity& q):
            GSFlow(q.volumeFraction(),
                   q.density(),
                   q.velocity(),
                   q.pressure(),
                   q.getGamma(),
                   q.getSolidVelocity())
                   {}
/*
 // Incorrect
    double volumeFraction(){
        return gasSolidState[0] / solidVelocity;
    }
    double density(){
        return gasSolidState[1] / gasSolidState[0];
    }
    double velocity(){
        return gasSolidState[2] / gasSolidState[1];
    }
    double pressure(){
        return (gasSolidState[3] / gasSolidState[1] - velocity() * velocity() / 2.0) * density() * (gamma - 1);
    }
*/
    void inverse() {
        gasSolidState = Vector({-gasSolidState[0], -gasSolidState[1], gasSolidState[2], -gasSolidState[3]});
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

    string toString(){
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

inline GSFlow toFlow(const GSQuantity& q){
    return {q.getGasSolidState(), q.getGamma(), q.getSolidVelocity()};
}

inline GSFlow zero(const GSQuantity& q){
    return {0,0,0,0,q.getGamma(), q.getSolidVelocity()};
}

#endif //TRANSPORTEQUATION_GSFLOW_H
