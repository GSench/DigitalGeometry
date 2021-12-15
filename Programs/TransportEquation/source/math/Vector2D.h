//
// Created by grigoriy.senchenok on 15.12.2021.
//

#ifndef TRANSPORTEQUATION_VECTOR2D_H
#define TRANSPORTEQUATION_VECTOR2D_H

#include "MathUtils.h"

class Vector2D {
public:
    double x = 0;
    double y = 0;
    double operator [](int xy) const {
        return xy==X ? x : y;
    }
};


#endif //TRANSPORTEQUATION_VECTOR2D_H
