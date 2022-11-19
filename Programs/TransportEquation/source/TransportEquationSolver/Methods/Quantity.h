//
// Created by grigoriy.senchenok on 18.11.2022.
//

#ifndef TRANSPORTEQUATION_QUANTITY_H
#define TRANSPORTEQUATION_QUANTITY_H

#include "../../math/Constants.h"
#include <vector>
#include <cstdlib>
#include <stdexcept>

using namespace std;

class Quantity {
private:
    int direction = X;
    int dimensions = 1;
    vector<Quantity> neighbours; // {left, right}|1D, bottom, top}|2D, back, forward}|3D
    int version = 0;
    void commit(int newVersion){
        if(version!=newVersion){
            version=newVersion;
            apply();
            for(Quantity& q: neighbours)
                q.commit(version);
        }
    }
protected:
    virtual void apply() = 0;
public:
    explicit Quantity(int dimensions):dimensions(dimensions),neighbours(dimensions*2){}

    virtual Quantity& prev(){
        return neighbours[direction*2];
    }

    virtual Quantity& next(){
        return neighbours[direction*2+1];
    }

    void setNeighbour(int dir, int lr, Quantity& n){
        neighbours[dir*2+lr] = n;
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

    virtual ~Quantity() = default;

};


#endif //TRANSPORTEQUATION_QUANTITY_H
