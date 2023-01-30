//
// Created by grigoriy.senchenok on 12.12.2022.
//

#ifndef TRANSPORTEQUATION_RBFLOW_H
#define TRANSPORTEQUATION_RBFLOW_H

#include "RBState.h"

class RBFlow {
private:
    double volumeFraction;
public:

    explicit RBFlow(double volumeFraction) : volumeFraction(volumeFraction) {}

    double getVolumeFraction() const {
        return volumeFraction;
    }

    // Flow operations

    RBFlow operator+(RBFlow& f) const {
        return RBFlow(volumeFraction+f.volumeFraction);
    }

    void operator+=(RBFlow& f) {
        volumeFraction+=f.volumeFraction;
    }

    RBFlow operator-(RBFlow& f) const {
        return RBFlow(volumeFraction-f.volumeFraction);
    }

    void operator-=(RBFlow& f) {
        volumeFraction-=f.volumeFraction;
    }

    // State operations

    RBState operator+(RBState& q) const {
        return {volumeFraction+q.getVolumeFraction(), q.getVelocities()};
    }

    RBState operator-(RBState& q) const {
        return {volumeFraction-q.getVolumeFraction(), q.getVelocities()};
    }

    // Scale operations

    RBFlow operator*(double s) const {
        return RBFlow(volumeFraction*s);
    }

    void operator*=(double s) {
        volumeFraction*=s;
    }

    RBFlow operator/(double s) const {
        return RBFlow(volumeFraction/s);
    }

    void operator/=(double s) {
        volumeFraction/=s;
    }
};


#endif //TRANSPORTEQUATION_RBFLOW_H
