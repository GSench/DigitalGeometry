//
// Created by grigoriy.senchenok on 12.12.2022.
//

#ifndef TRANSPORTEQUATION_SFLOW_H
#define TRANSPORTEQUATION_SFLOW_H

#include "SQuantity.h"

class SFlow {
private:
    double volumeFraction;
public:

    explicit SFlow(double volumeFraction) : volumeFraction(volumeFraction) {}

    double getVolumeFraction() const {
        return volumeFraction;
    }

    // Flow operations

    SFlow operator+(const SFlow& f) const {
        return SFlow(volumeFraction + f.volumeFraction);
    }

    void operator+=(const SFlow& f) {
        volumeFraction+=f.volumeFraction;
    }

    SFlow operator-(const SFlow& f) const {
        return SFlow(volumeFraction - f.volumeFraction);
    }

    void operator-=(const SFlow& f) {
        volumeFraction-=f.volumeFraction;
    }

    // State operations

    SQuantity operator+(const SQuantity& q) const {
        return {volumeFraction+q.getVolumeFraction(), q.getVelocities()};
    }

    SQuantity friend operator+(const SQuantity& q, const SFlow& f) {
        return {q.getVolumeFraction()+f.getVolumeFraction(), q.getVelocities()};
    }

    SQuantity operator-(const SQuantity& q) const {
        return {volumeFraction-q.getVolumeFraction(), q.getVelocities()};
    }

    SQuantity friend operator-(const SQuantity& q, const SFlow& f) {
        return {q.getVolumeFraction()-f.getVolumeFraction(), q.getVelocities()};
    }

    // Scale operations

    SFlow operator*(double s) const {
        return SFlow(volumeFraction * s);
    }

    void operator*=(double s) {
        volumeFraction*=s;
    }

    SFlow operator/(double s) const {
        return SFlow(volumeFraction / s);
    }

    void operator/=(double s) {
        volumeFraction/=s;
    }
};


#endif //TRANSPORTEQUATION_SFLOW_H
