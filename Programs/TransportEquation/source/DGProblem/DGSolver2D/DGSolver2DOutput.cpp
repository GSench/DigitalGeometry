//
// Created by grigoriy.senchenok on 07.05.2022.
//

#include "DGSolver2DOutput.h"

DGSolver2DOutput no2DOutputDG(){
    return {false, false, "", "", false, 0, 0};
}

DGSolver2DOutput minimal2DOutputDG(const string& filePathTE, const string& filePathEE, int NTimeSteps){
    return {true, false, filePathTE, filePathEE, true, NTimeSteps, 50};
}
