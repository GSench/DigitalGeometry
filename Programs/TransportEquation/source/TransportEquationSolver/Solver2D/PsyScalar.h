//
// Created by GSench on 14.12.2021.
//

#ifndef TRANSPORTEQUATION_PSYSCALAR_H
#define TRANSPORTEQUATION_PSYSCALAR_H

#include <vector>
#include <cstdlib>
#include <fstream>
#include "../../Utils/ArrayUtils.h"

using namespace std;

const int XL = 0;
const int XR = 1;
const int YL = 2;
const int YR = 3;

class PsyScalar {
private:
    int widthI = 100;
    int heightI = 100;
    double width = 1;
    double height = 1;
    double dx = width/widthI;
    double dy = height/heightI;
    vector<double> world;
public:
    PsyScalar(int widthI, int heightI, double width, double height):
        widthI(widthI),
        heightI(heightI),
        width(width),
        height(height),
        dx(width/widthI),
        dy(height/heightI),
        world(widthI * heightI){}
    double get(int ix, int iy){
        //xi %= widthI;
        //yi %= heightI;
        return world[iy * widthI + ix];
    }
    void set(int ix, int iy, double val){
        //xi %= widthI;
        //yi %= heightI;
        world[iy * widthI + ix] = val;
    }
    double getWithOffset(int ix, int iy, int offsetIX, int offsetIY){
        ix = (ix+offsetIX) % widthI;
        ix += (ix<0) * widthI;
        iy = (iy+offsetIY) % heightI;
        iy += (iy<0) * heightI;
        return world[iy * widthI + ix];
    }
    void getCellBounds(int xi, int yi, double cell[]) const {
        //xi %= widthI;
        //yi %= heightI;
        cell[XL] = xi * dx;
        cell[XR] = (xi+1) * dx;
        cell[YL] = yi * dy;
        cell[YR] = (yi+1) * dy;
    }
    void printToFile(ofstream& file, bool printAxes){
        // TODO print Axes if printAxes
        for(int iy = 0; iy < heightI; iy++){
            for(int ix = 0; ix < widthI; ix++)
                file << world[iy*widthI + ix] << '\t';
            file << endl;
        }
    }
};


#endif //TRANSPORTEQUATION_PSYSCALAR_H