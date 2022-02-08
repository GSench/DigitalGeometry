//
// Created by grigoriy.senchenok on 08.02.2022.
//

#include "VectorField2D.h"

VectorField2D getStaticVF2D(const Vector2D &v2D, int width, int height){
    return {
            [=](int xi, int yi) -> Vector2D {
                return v2D;
            }, width, height
    };
}
