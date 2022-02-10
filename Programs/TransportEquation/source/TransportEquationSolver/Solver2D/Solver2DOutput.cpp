//
// Created by grigoriy.senchenok on 08.02.2022.
//

#include "Solver2DOutput.h"

Solver2DOutput no2DOutput(){
    return {false, false, "", false, 0, 0};
}

Solver2DOutput minimal2DOutput(const string& filePath, int NTimeSteps){
    return {true, false, filePath, true, NTimeSteps, 50};
}
