//
// Created by grigoriy.senchenok on 07.02.2022.
//

#ifndef TRANSPORTEQUATION_AREA2D_H
#define TRANSPORTEQUATION_AREA2D_H

#include <vector>
#include "../Solver1D/Solver1DInstances.h"

using namespace std;

const int X = 0;
const int Y = 1;

class Area2D : public LineInterface {
private:
    vector<double> scalarFunction;
    int currentXi = 0;
    int currentYi = 0;
    int direction = X;
    int width;
    int height;
public:
    Area2D(const vector<double> &scalarFunction,
           int width,
           int height):
            scalarFunction(scalarFunction),
            width(width),
            height(height)
            {}

    double operator[](int i) override {
        if(direction == X){
            if (i < 0 || i >= width) return 0;
            return scalarFunction[currentYi * width + i];
        }
        if(direction == Y){
            if (i < 0 || i >= height) return 0;
            return scalarFunction[i * width + currentXi];
        }
        return 0;
    }

    void set(int i, double val) override {
        if(direction == X)
            scalarFunction[currentYi * width + i] = val;
        if(direction == Y)
            scalarFunction[i * width + currentXi] = val;
    }

    int size() override {
        return direction==X ? width : height;
    }

    void lineOver(int dir, int xy){
        direction = dir;
        currentXi = xy * (dir!=X);
        currentYi = xy * (dir!=Y);
    }
};


#endif //TRANSPORTEQUATION_AREA2D_H
