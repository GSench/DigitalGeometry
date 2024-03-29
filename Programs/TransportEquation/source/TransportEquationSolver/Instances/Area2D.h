//
// Created by grigoriy.senchenok on 07.02.2022.
//

#ifndef TRANSPORTEQUATION_AREA2D_H
#define TRANSPORTEQUATION_AREA2D_H

#include <vector>
#include "TESolver1DInstances.h"
#include "../../math/Vector2D.h"

using namespace std;

class Area2D : public LineInterface {
private:
    vector<double> scalarFunction;
    int currentXi = 0;
    int currentYi = 0;
    int direction = X;
    int width;
    int height;
public:
    Area2D(int width,
           int height):
            scalarFunction(vector<double>(width*height, 0)),
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

    double get(int x, int y) {
        return scalarFunction[y*width + x];
    }

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
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

    void projectX(int y){
        direction = X;
        currentXi = 0;
        currentYi = y;
    }

    void projectY(int x){
        direction = Y;
        currentXi = x;
        currentYi = 0;
    }

    void drawRect(double val, int startX, int startY, int sizeX, int sizeY){
        for(int y=min(startY, height); y<min(startY+sizeY, height); y++)
            for(int x=min(startX, width); x<min(startX+sizeX, width); x++)
                scalarFunction[y*width + x] = val;
    }

    // TODO drawStruct(vector<double> struct, int startX, int startY, int sizeX, int sizeY){}
};


#endif //TRANSPORTEQUATION_AREA2D_H
