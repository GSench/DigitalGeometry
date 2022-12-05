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
        quantity(quantity)
    {}

    explicit Quantity(Vector& cellPos, double dx, T quantity): // square, cube
        dimensions(cellPos.dim),
        neighbours(cellPos.dim*2),
        cellPos(cellPos),
        cellSize(vector<double>(cellPos.dim, dx)),
        quantity(quantity)
    {}

    explicit Quantity(double cellPos, double dx, T quantity): // 1D
            dimensions(1),
            neighbours(2),
            cellPos(cellPos),
            cellSize(dx),
            quantity(quantity)
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

    void fillQuantity(int fromCell, int toCell, T newQuantity){
        Quantity<T>* fIter = *this;
        for(int i=0; i<fromCell; i++){
            fIter = fIter->next();
        }
        for(int i=fromCell; i<toCell; i++){
            fIter->setQuantity(newQuantity);
            fIter = fIter->next();
        }
    }

};

template<typename T>
Quantity<T>& generate1DMesh(int cellCount, double dx, T defaultValue);

#endif //TRANSPORTEQUATION_QUANTITY_H
