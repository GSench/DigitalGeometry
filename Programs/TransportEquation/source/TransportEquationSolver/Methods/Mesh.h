//
// Created by grigoriy.senchenok on 18.11.2022.
//

#ifndef TRANSPORTEQUATION_MESH_H
#define TRANSPORTEQUATION_MESH_H

#include "../../math/Vector.h"
#include <vector>
#include <cstdlib>
#include <stdexcept>

using namespace std;

const int L = 0;
const int R = 1;

template<typename T>
class Mesh {
private:
    int direction = X;
    int dimensions = 1;
    vector<Mesh*> neighbours; // {left, right}|1D, bottom, top}|2D, back, forward}|3D
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
            for(Mesh* q: neighbours)
                if(q != NULL)
                    q->apply(version);
        }
    }
public:
    explicit Mesh(Vector& cellPos, Vector& cellSize, T quantity):
        dimensions(cellPos.getDim()),
        neighbours(cellPos.getDim()*2),
        cellPos(cellPos),
        cellSize(cellSize),
        quantity(quantity),
        newQuantity(quantity)
    {}

    explicit Mesh(Vector& cellPos, double dx, T quantity): // square, cube
        dimensions(cellPos.getDim()),
        neighbours(cellPos.getDim()*2),
        cellPos(cellPos),
        cellSize(vector<double>(cellPos.getDim(), dx)),
        quantity(quantity),
        newQuantity(quantity)
    {}

    explicit Mesh(double cellPos, double dx, T quantity): // 1D
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

    Mesh* prev(){
        return neighbours[direction*2];
    }

    Mesh* next(){
        return neighbours[direction*2+1];
    }

    void setNeighbour(int dir, int lr, Mesh& n){
        neighbours[dir*2+lr] = &n;
    }

    double x() const {
        return cellPos[direction];
    }

    double dx() const {
        return cellSize[direction];
    }

    double xL() const {
        return cellPos[direction]-cellSize[direction]/2;
    }

    double xR() const {
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

    void setQuantity(int cell, T q){
        Mesh<T>* fIter = this;
        for(int i=0; i<cell; i++)
            fIter = fIter->next();
        fIter->setQuantity(q);
    }

    void fillQuantity(int fromCell, int toCell, T q){
        Mesh<T>* fIter = this;
        for(int i=0; i<fromCell; i++)
            fIter = fIter->next();
        for(int i=fromCell; i<toCell; i++){
            fIter->setQuantity(q);
            fIter = fIter->next();
        }
    }

};

template<typename T>
pair<Mesh<T>*,Mesh<T>*> generate1DMesh(int cellCount, double posDelta, double cellSize, double offset, T defaultValue){
    Mesh<T>* mesh = new Mesh<T>(offset, cellSize, defaultValue);
    mesh->markBorder();
    Mesh<T>* meshIter = mesh;
    for(int i=0; i<cellCount-2; i++){
        Mesh<T>* nextCell = new Mesh<T>(meshIter->x() + posDelta, cellSize, defaultValue);
        nextCell->setNeighbour(X, L, *meshIter);
        meshIter->setNeighbour(X, R, *nextCell);
        meshIter = meshIter->next();
    }
    Mesh<T>* finalCell = new Mesh<T>(meshIter->x() + posDelta, cellSize, defaultValue);
    finalCell->markBorder();
    finalCell->setNeighbour(X, L, *meshIter);
    meshIter->setNeighbour(X, R, *finalCell);
    return {mesh, finalCell};
}

template<typename T>
Mesh<T> generate1DPeriodicMesh(int cellCount, double posDelta, double cellSize, double offset, T defaultValue){
    pair<Mesh<T>*,Mesh<T>*> rawMesh = generate1DMesh<T>(cellCount, posDelta, cellSize, offset, defaultValue);
    rawMesh.first->setNeighbour(X, L, *(rawMesh.second));
    rawMesh.second->setNeighbour(X, R, *(rawMesh.first));
    return *(rawMesh.first);
}

template<typename T>
Mesh<T> generate1DBorderedMesh(int cellCount, double posDelta, double cellSize, double offset, T defaultValue, T outOfBoundsValueL, T outOfBoundsValueR){
    pair<Mesh<T>*,Mesh<T>*> rawMesh = generate1DMesh<T>(cellCount, posDelta, cellSize, offset, defaultValue);
    Mesh<T>* lBorder = new Mesh<T>(rawMesh.first->x() - posDelta, cellSize, outOfBoundsValueL);
    rawMesh.first->setNeighbour(X, L, *lBorder);
    Mesh<T>* rBorder = new Mesh<T>(rawMesh.second->x() + posDelta, cellSize, outOfBoundsValueR);
    rawMesh.second->setNeighbour(X, R, *rBorder);
    return *(rawMesh.first);
}

inline int inverseDirLR(int dir){
    return (1-(dir*2-1))/2;
}

#endif //TRANSPORTEQUATION_MESH_H
