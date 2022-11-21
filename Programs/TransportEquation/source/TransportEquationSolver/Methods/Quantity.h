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

class Quantity {
private:
    int direction = X;
    int dimensions = 1;
    vector<Quantity*> neighbours; // {left, right}|1D, bottom, top}|2D, back, forward}|3D
    int version = 0;

    Vector3D cellPos;
    Vector3D cellSize;

    void commit(int newVersion){
        if(version!=newVersion){
            version=newVersion;
            apply();
            for(Quantity* q: neighbours)
                q->commit(version);
        }
    }
protected:
    virtual void apply() { }
public:
    explicit Quantity(Vector3D& cellPos, Vector3D& cellSize):
        dimensions(cellPos.dim()),
        neighbours(cellPos.dim()*2),
        cellPos(cellPos),
        cellSize(cellSize)
    {}

    explicit Quantity(Vector3D& cellPos, double dx): // square, cube
        dimensions(cellPos.dim()),
        neighbours(cellPos.dim()*2),
        cellPos(cellPos),
        cellSize(dx)
    {}

    explicit Quantity(double cellPos, double dx): // 1D
            dimensions(1),
            neighbours(2),
            cellPos(cellPos),
            cellSize(dx)
    {}

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

    void commit(){
        commit(version+1);
    }

    //virtual ~Quantity() = default;

};


#endif //TRANSPORTEQUATION_QUANTITY_H
