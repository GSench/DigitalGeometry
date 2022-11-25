//
// Created by grigoriy.senchenok on 18.11.2022.
//

#ifndef TRANSPORTEQUATION_QUANTITY_H
#define TRANSPORTEQUATION_QUANTITY_H

#include "../../math/Constants.h"
#include "../../math/Vector2D.h"
#include "../../math/Vector3D.h"
#include <vector>
#include <cstdlib>
#include <stdexcept>

using namespace std;

template<typename T>
class Quantity {
private:
    int direction = X;
    int dimensions = 1;
    vector<Quantity*> neighbours; // {left, right}|1D, bottom, top}|2D, back, forward}|3D
    int version = 0;

    // these variables are values, passing Vector1D/2D leads to object slicing, so mind that returning them as references returns Vector3D, and no cast will help!
    // if you need to get these values as references to its original Vectors' dimensions, make them pointers and init them in constructors as copy of passed reference, or as reference to copied passed objects
    Vector3D cellPos;
    Vector3D cellSize;

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
    explicit Quantity(Vector3D& cellPos, Vector3D& cellSize, T quantity):
        dimensions(cellPos.dim()),
        neighbours(cellPos.dim()*2),
        cellPos(cellPos),
        cellSize(cellSize),
        quantity(quantity)
    {}

    explicit Quantity(Vector3D& cellPos, double dx, T quantity): // square, cube
        dimensions(cellPos.dim()),
        neighbours(cellPos.dim()*2),
        cellPos(cellPos),
        cellSize(dx),
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

    virtual Quantity& prev(){
        return *neighbours[direction*2];
    }

    virtual Quantity& next(){
        return *neighbours[direction*2+1];
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

    //virtual ~Quantity() = default;

};


#endif //TRANSPORTEQUATION_QUANTITY_H
