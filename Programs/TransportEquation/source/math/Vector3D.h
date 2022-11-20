//
// Created by grigoriy.senchenok on 15.12.2021.
//

#ifndef TRANSPORTEQUATION_VECTOR3D_H
#define TRANSPORTEQUATION_VECTOR3D_H

#include <stdexcept>

#include "Constants.h"

using namespace std;

class Vector3D {
public:
    double x = 0;
    double y = 0;
    double z = 0;

    Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}
    Vector3D(double x, double y) : x(x), y(y), z(0) {}
    explicit Vector3D(double x) : x(x), y(0), z(0) {}
    Vector3D() : x(0), y(0), z(0) {}

    virtual int dim() {return 3;};

    double operator [](int xyz) const {
        switch (xyz) {
            case X: return x;
            case Y: return y;
            case Z: return z;
            default: throw invalid_argument( "invalid value passed into Vector[]" );
        }
    }

    Vector3D operator+(Vector3D v) const{
        return {x+v.x, y+v.y, z+v.z};
    }

    void operator+=(Vector3D v) {
        x+=v.x; y+=v.y; z+=v.z;
    }

    Vector3D operator-(Vector3D v) const{
        return {x-v.x, y-v.y, z-v.z};
    }

    void operator-=(Vector3D v) {
        x-=v.x; y-=v.y; z-=v.z;
    }

    Vector3D operator*(double s) const{
        return {x*s, y*s, z*s};
    }

    void operator*=(double s) {
        x*=s; y*=s; z*=s;
    }

    Vector3D operator/(double s) const{
        return {x/s, y/s, z/s};
    }

    void operator/=(double s) {
        x/=s; y/=s; z/=s;
    }
};

#endif //TRANSPORTEQUATION_VECTOR3D_H
