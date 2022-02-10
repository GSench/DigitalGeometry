//
// Created by grigoriy.senchenok on 08.02.2022.
//

#ifndef TRANSPORTEQUATION_VECTORFIELD2D_H
#define TRANSPORTEQUATION_VECTORFIELD2D_H

#include "../../math/Vector2D.h"
#include "../Solver1D/Solver1DInstances.h"

class VectorField2D : public LineInterface{
private:
    function<Vector2D(int, int)> u;
    int width;
    int height;
    int currentXi = 0;
    int currentYi = 0;
    int direction = X;
public:
    VectorField2D(const function<Vector2D(int, int)> &u,
                  int width,
                  int height):
                  u(u),
                  width(width),
                  height(height)
                  {}

    double operator[](int i) override {
        if(direction == X){
            return u(i, currentYi)[X];
        }
        if(direction == Y){
            return u(currentXi, i)[Y];
        }
        return 0;
    }

    void set(int i, double val) override {

    }

    int size() override {
        return direction==X ? width : height;
    }

    void projectX(int y){
        direction = X;
        currentXi = 0;
        currentYi = y;
    }

    void projectY(int x){
        direction = Y;
        currentXi = x;
        currentYi = 0;
    }
};

VectorField2D getStaticVF2D(const Vector2D &v2D, int width, int height);

#endif //TRANSPORTEQUATION_VECTORFIELD2D_H
