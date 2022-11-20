//
// Created by grigoriy.senchenok on 15.12.2021.
//

#ifndef TRANSPORTEQUATION_VECTOR2D_H
#define TRANSPORTEQUATION_VECTOR2D_H

#include "Vector3D.h"

class Vector2D : public Vector3D {
private:
    Vector2D(double x, double y, double z) : Vector3D(x, y, z) {}

public:
    int dim() override {return 2;};

    Vector2D(double x, double y) : Vector3D(x, y) {}
    explicit Vector2D(double x) : Vector3D(x) {}
    Vector2D() : Vector3D() {}
};

#endif //TRANSPORTEQUATION_VECTOR2D_H
