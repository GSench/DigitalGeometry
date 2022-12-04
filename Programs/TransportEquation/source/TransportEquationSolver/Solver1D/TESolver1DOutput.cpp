//
// Created by grigoriy.senchenok on 21.12.2021.
//

#include "TESolver1DOutput.h"

template<typename T, typename U>
TESolver1DOutput<T, U> noOutput(){
    return {false, false, false, false, false, "", false, 0, 0, false};
}

template<typename T, typename U>
TESolver1DOutput<T,U> minimal1DOutput(const string& filePath, int NTimeSteps){
    return {true, false, false, true, false, filePath, true, NTimeSteps, 50, false};
}

template<typename T, typename U>
TESolver1DOutput<T,U> maximal1DOutput(const string& filePath, int NTimeSteps){
    return {true, false, false, true, false, filePath, false, NTimeSteps, 50, false};
}

template<typename T, typename U>
TESolver1DOutput<T,U> normal1DOutput(const string& filePath, int NTimeSteps){
    return { true, true, true, true, true, filePath, true, NTimeSteps, 50, true};
}

template<typename T, typename U>
TESolver1DOutput<T,U> jupyter1DOutput(const string& filePath, int NTimeSteps){
    return { true, true, true, false, false, filePath, true, NTimeSteps, 100, true};
}