//
// Created by grigoriy.senchenok on 15.12.2021.
//

#ifndef TRANSPORTEQUATION_VECTOR2D_H
#define TRANSPORTEQUATION_VECTOR2D_H

const int X = 0;
const int Y = 1;

class Vector2D {
public:
    double x = 0;
    double y = 0;

    Vector2D(double x, double y) : x(x), y(y) {}
    Vector2D() : x(0), y(0) {}

    double operator [](int xy) const {
        return xy==X ? x : y;
    }

    Vector2D operator+(Vector2D v) const{
        return {x+v.x, y+v.y};
    }

    void operator+=(Vector2D v) {
        x+=v.x; y+=v.y;
    }

    Vector2D operator-(Vector2D v) const{
        return {x-v.x, y-v.y};
    }

    void operator-=(Vector2D v) {
        x-=v.x; y-=v.y;
    }

    Vector2D operator*(double s) const{
        return {x*s, y*s};
    }

    void operator*=(double s) {
        x*=s; y*=s;
    }

    Vector2D operator/(double s) const{
        return {x/s, y/s};
    }

    void operator/=(double s) {
        x/=s; y/=s;
    }
};

#endif //TRANSPORTEQUATION_VECTOR2D_H
