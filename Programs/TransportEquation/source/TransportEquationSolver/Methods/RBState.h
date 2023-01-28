//
// Created by grigoriy.senchenok on 12.12.2022.
//

#ifndef TRANSPORTEQUATION_RBSTATE_H
#define TRANSPORTEQUATION_RBSTATE_H

#include <utility>

#include "TimeStepVelocity.h"
#include "RBFlow.h"

class RBState {
private:
    double volumeFraction = 1;
    vector<TimeStepVelocity> transportVelocities;
public:
    RBState(double volumeFraction, vector<TimeStepVelocity>& transportVelocities) :
            volumeFraction(volumeFraction), transportVelocities(transportVelocities)
        {}

    double getVolumeFraction() const{
        return volumeFraction;
    }

    TimeStepVelocity velocity(int dir, int lr){
        return transportVelocities[dir*2+lr];
    }

    double currVelocityDir(int dir, int lr){
        return transportVelocities[dir*2+lr].getU()[dir];
    }

    double nextVelocityDir(int dir, int lr){
        return transportVelocities[dir*2+lr].getUNext()[dir];
    }

    // State operations

    RBState operator+(RBState& q) {
        return {volumeFraction+q.volumeFraction, transportVelocities};
    }

    void operator+=(RBState& q) {
        volumeFraction+=q.volumeFraction;
    }

    RBState operator-(RBState& q) {
        return {volumeFraction-q.volumeFraction, transportVelocities};
    }


    void operator-=(RBState& q) {
        volumeFraction-=q.volumeFraction;
    }

    // Flow operations

    RBState operator+(RBFlow f) {
        return {volumeFraction+f.getVolumeFraction(), transportVelocities};
    }

    void operator+=(RBFlow f) {
        volumeFraction+=f.getVolumeFraction();
    }

    RBState operator-(RBFlow f) {
        return {volumeFraction-f.getVolumeFraction(), transportVelocities};
    }

    void operator-=(RBFlow f) {
        volumeFraction-=f.getVolumeFraction();
    }

    // Scale operations

    RBState operator*(double s) {
        return {volumeFraction*s, transportVelocities};
    }

    void operator*=(double s) {
        volumeFraction*=s;
    }

    RBState operator/(double s) {
        return {volumeFraction/s, transportVelocities};
    }

    void operator/=(double s) {
        volumeFraction/=s;
    }
};


#endif //TRANSPORTEQUATION_RBSTATE_H
