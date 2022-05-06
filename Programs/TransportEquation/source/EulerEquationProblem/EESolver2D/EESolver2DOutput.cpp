//
// Created by gsench on 02.05.22.
//

#include "EESolver2DOutput.h"

EESolver2DOutput no2DOutputEE(){
    return {false, false, "", false, 0, 0};
}

EESolver2DOutput minimal2DOutputEE(const string& filePath, int NTimeSteps){
    return {true, false, filePath, true, NTimeSteps, 50};
}
