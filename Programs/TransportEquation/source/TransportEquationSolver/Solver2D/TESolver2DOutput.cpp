//
// Created by grigoriy.senchenok on 08.02.2022.
//

#include "TESolver2DOutput.h"

TESolver2DOutput no2DOutput(){
    return {false, false, "", false, 0, 0};
}

TESolver2DOutput minimal2DOutput(const string& filePath, int NTimeSteps){
    return {true, false, filePath, true, NTimeSteps, 50};
}
