//
// Created by grigoriy.senchenok on 05.12.2022.
//

#include "Quantity.h"


template<typename T>
Quantity<T>& generate1DMesh(int cellCount, double dx, T defaultValue){
    Quantity<T> mesh(dx/2, dx, defaultValue);
    mesh.markBorder();
    Quantity<T>* meshIter = &mesh;
    for(int i=0; i<cellCount-2; i++){
        Quantity<T> nextCell(meshIter->x()+dx, dx, defaultValue);
        nextCell.setNeighbour(X, L, meshIter);
        meshIter->setNeighbour(X, R, nextCell);
        meshIter = meshIter->next();
    }
    Quantity<T> finalCell(meshIter->x()+dx, dx, defaultValue);
    finalCell.setNeighbour(X, L, meshIter);
    meshIter->setNeighbour(X, R, finalCell);
    return mesh;
}