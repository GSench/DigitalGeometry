//
// Created by grigoriy.senchenok on 12.12.2022.
//

#ifndef TRANSPORTEQUATION_RBSTATE_H
#define TRANSPORTEQUATION_RBSTATE_H

#include <utility>

#include "TimeStepVelocity.h"

class RBState {
private:
    double volumeFraction = 1;
    vector<TimeStepVelocity> transportVelocities;
public:
    RBState(double volumeFraction, vector<TimeStepVelocity> transportVelocities) :
            volumeFraction(volumeFraction), transportVelocities(std::move(transportVelocities))
        {}

    double getVolumeFraction() const{
        return volumeFraction;
    }

    TimeStepVelocity velocity(int dir, int lr){
        return transportVelocities[dir*2+lr];
    }

    vector<TimeStepVelocity> getVelocities() const {
        return transportVelocities;
    }

    double currVelocityDir(int dir, int lr){
        return transportVelocities[dir*2+lr].getU()[dir];
    }

    double nextVelocityDir(int dir, int lr){
        return transportVelocities[dir*2+lr].getUNext()[dir];
    }

    // State operations

    RBState operator+(const RBState& q) const {
        return {volumeFraction+q.volumeFraction, transportVelocities};
    }

    void operator+=(const RBState& q) {
        volumeFraction+=q.volumeFraction;
    }

    RBState operator-(const RBState& q) const {
        return {volumeFraction-q.volumeFraction, transportVelocities};
    }


    void operator-=(const RBState& q) {
        volumeFraction-=q.volumeFraction;
    }

    // Scale operations

    RBState operator*(double s) const {
        return {volumeFraction*s, transportVelocities};
    }

    void operator*=(double s) {
        volumeFraction*=s;
    }

    RBState operator/(double s) const {
        return {volumeFraction/s, transportVelocities};
    }

    void operator/=(double s) {
        volumeFraction/=s;
    }
};


#endif //TRANSPORTEQUATION_RBSTATE_H
