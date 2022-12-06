//
// Created by grigoriy.senchenok on 18.11.2022.
//

#ifndef TRANSPORTEQUATION_QUANTITY_H
#define TRANSPORTEQUATION_QUANTITY_H

#include "../../math/Vector.h"
#include <vector>
#include <cstdlib>
#include <stdexcept>

using namespace std;

const int L = 0;
const int R = 1;

template<typename T>
class Quantity {
private:
    int direction = X;
    int dimensions = 1;
    vector<Quantity*> neighbours; // {left, right}|1D, bottom, top}|2D, back, forward}|3D
    int version = 0;

    // these variables are values, passing Vector1D/2D leads to object slicing, so mind that returning them as references returns Vector3D, and no cast will help!
    // if you need to get these values as references to its original Vectors' dimensions, make them pointers and init them in constructors as copy of passed reference, or as reference to copied passed objects
    Vector cellPos;
    Vector cellSize;

    bool border = false;

    T quantity;
    T newQuantity;

    void apply(int newVersion){
        if(version!=newVersion){
            version=newVersion;
            quantity = newQuantity;
            for(Quantity* q: neighbours)
                q->apply(version);
        }
    }
public:
    explicit Quantity(Vector& cellPos, Vector& cellSize, T quantity):
        dimensions(cellPos.dim),
        neighbours(cellPos.dim*2),
        cellPos(cellPos),
        cellSize(cellSize),
        quantity(quantity),
        newQuantity(quantity)
    {}

    explicit Quantity(Vector& cellPos, double dx, T quantity): // square, cube
        dimensions(cellPos.dim),
        neighbours(cellPos.dim*2),
        cellPos(cellPos),
        cellSize(vector<double>(cellPos.dim, dx)),
        quantity(quantity),
        newQuantity(quantity)
    {}

    explicit Quantity(double cellPos, double dx, T quantity): // 1D
            dimensions(1),
            neighbours(2),
            cellPos(cellPos),
            cellSize(dx),
            quantity(quantity),
            newQuantity(quantity)
    {}

    T getQuantity() const {
        return quantity;
    }

    void setQuantity(T q) {
        newQuantity = q;
    }

    Quantity* prev(){
        return neighbours[direction*2];
    }

    Quantity* next(){
        return neighbours[direction*2+1];
    }

    void setNeighbour(int dir, int lr, Quantity& n){
        neighbours[dir*2+lr] = &n;
    }

    double x(){
        return cellPos[direction];
    }

    double dx(){
        return cellSize[direction];
    }

    double xL(){
        return cellPos[direction]-cellSize[direction]/2;
    }

    double xR(){
        return cellPos[direction]+cellSize[direction]/2;
    }

    void setXDir() {
        direction = X;
    }

    void setYDir() {
        if(dimensions<2) throw domain_error("attempt to switch Y direction in 1D quantity");
        direction = Y;
    }

    void setZDir() {
        if(dimensions<3) throw domain_error("attempt to switch Z direction in 1D/2D quantity");
        direction = Z;
    }

    int getDirection() const {
        return direction;
    }

    bool isBorder() const {
        return border;
    }

    void markBorder(){
        border = true;
    }

    void markIntermediate(){
        border = false;
    }

    void apply(){
        apply(version+1);
    }

    void fillQuantity(int fromCell, int toCell, T q){
        Quantity<T>* fIter = this;
        for(int i=0; i<fromCell; i++)
            fIter = fIter->next();
        for(int i=fromCell; i<toCell; i++){
            fIter->setQuantity(q);
            fIter = fIter->next();
        }
    }

};

template<typename T>
pair<Quantity<T>*,Quantity<T>*> generate1DMesh(int cellCount, double posDelta, double cellSize, double offset, T defaultValue){
    Quantity<T>* mesh = new Quantity<T>(offset, cellSize, defaultValue);
    mesh->markBorder();
    Quantity<T>* meshIter = mesh;
    for(int i=0; i<cellCount-2; i++){
        Quantity<T>* nextCell = new Quantity<T>(meshIter->x() + posDelta, cellSize, defaultValue);
        nextCell->setNeighbour(X, L, *meshIter);
        meshIter->setNeighbour(X, R, *nextCell);
        meshIter = meshIter->next();
    }
    Quantity<T>* finalCell = new Quantity<T>(meshIter->x() + posDelta, cellSize, defaultValue);
    finalCell->markBorder();
    finalCell->setNeighbour(X, L, *meshIter);
    meshIter->setNeighbour(X, R, *finalCell);
    return {mesh, finalCell};
}

template<typename T>
Quantity<T>& generate1DPeriodicMesh(int cellCount, double posDelta, double cellSize, double offset, T defaultValue){
    pair<Quantity<T>*,Quantity<T>*> rawMesh = generate1DMesh<T>(cellCount, posDelta, cellSize, offset, defaultValue);
    rawMesh.first->setNeighbour(X, L, *(rawMesh.second));
    rawMesh.second->setNeighbour(X, R, *(rawMesh.first));
    return *(rawMesh.first);
}

template<typename T>
Quantity<T>& generate1DBorderedMesh(int cellCount, double posDelta, double cellSize, double offset, T defaultValue, T outOfBoundsValue){
    pair<Quantity<T>*,Quantity<T>*> rawMesh = generate1DMesh<T>(cellCount, posDelta, cellSize, offset, defaultValue);
    Quantity<T>* lBorder = new Quantity<T>(rawMesh.first->x() - posDelta, cellSize, outOfBoundsValue);
    rawMesh.first->setNeighbour(X, L, *lBorder);
    Quantity<T>* rBorder = new Quantity<T>(rawMesh.second->x() + posDelta, cellSize, outOfBoundsValue);
    rawMesh.second->setNeighbour(X, R, *rBorder);
    return *(rawMesh.first);
}

#endif //TRANSPORTEQUATION_QUANTITY_H
