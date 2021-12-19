//
// Created by grigoriy.senchenok on 15.12.2021.
//

#ifndef TRANSPORTEQUATION_VECTORFIELD2D_H
#define TRANSPORTEQUATION_VECTORFIELD2D_H


#include <vector>
#include "Vector2D.h"

using namespace std;

class VectorField2D {
private:
    vector<Vector2D> vectors;
    int widthI;
    int heightI;
public:
    VectorField2D(int widthI, int heightI):
    widthI(widthI),
    heightI(heightI),
    vectors(widthI * heightI){}

    Vector2D getVectorAt(int iX, int iY){
        return vectors[iY * widthI + iX];
    }
};


#endif //TRANSPORTEQUATION_VECTORFIELD2D_H
