//
// Created by grigoriy.senchenok on 28.01.2023.
//

#include "VectorPrefabs.h"

Vector zero(int dim){
    return Vector(dim);
}

Vector zero(const Vector& dimVector){
    return zero(dimVector.dim);
}

Vector unit(int dim){
    return {dim, 1.0};
}

Vector unit(const Vector& dimVector){
    return unit(dimVector.dim);
}