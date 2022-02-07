//
// Created by grigoriy.senchenok on 21.12.2021.
//

#include "Solver1DOutput.h"

Solver1DOutput noOutput(){
    return {false, false, false, false, false, "", false, 0, 0, false};
}

Solver1DOutput minimal1DOutput(const string& filePath, int NTimeSteps){
    return {true, false, false, true, false, filePath, true, NTimeSteps, 50, false};
}

Solver1DOutput normal1DOutput(const string& filePath, int NTimeSteps){
    return { true, true, true, true, true, filePath, true, NTimeSteps, 50, true};
}

Solver1DOutput jupyter1DOutput(const string& filePath, int NTimeSteps){
    return { true, true, true, false, false, filePath, true, NTimeSteps, 100, true};
}