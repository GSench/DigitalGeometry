//
// Created by grigoriy.senchenok on 08.02.2022.
//

#include "Area1D.h"

Area1D rightHalfFilled(int cellCount, bool periodicBoundaries){
    vector<double> f(cellCount, 0);
    for(int i=cellCount/2; i<cellCount; i++) f[i] = 1;
    return {periodicBoundaries, f};
}
