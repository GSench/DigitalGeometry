//
// Created by grigoriy.senchenok on 12.12.2022.
//

#ifndef TRANSPORTEQUATION_SQUANTITY_H
#define TRANSPORTEQUATION_SQUANTITY_H

#include <utility>

#include "TimeStepVelocity.h"

class SQuantity {
private:
    double volumeFraction = 1;
    vector<TimeStepVelocity> transportVelocities;
public:
    SQuantity(double volumeFraction, vector<TimeStepVelocity> transportVelocities) :
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

    SQuantity operator+(const SQuantity& q) const {
        return {volumeFraction+q.volumeFraction, transportVelocities};
    }

    void operator+=(const SQuantity& q) {
        volumeFraction+=q.volumeFraction;
    }

    SQuantity operator-(const SQuantity& q) const {
        return {volumeFraction-q.volumeFraction, transportVelocities};
    }


    void operator-=(const SQuantity& q) {
        volumeFraction-=q.volumeFraction;
    }

    // Scale operations

    SQuantity operator*(double s) const {
        return {volumeFraction*s, transportVelocities};
    }

    void operator*=(double s) {
        volumeFraction*=s;
    }

    SQuantity operator/(double s) const {
        return {volumeFraction/s, transportVelocities};
    }

    void operator/=(double s) {
        volumeFraction/=s;
    }
};


#endif //TRANSPORTEQUATION_SQUANTITY_H
