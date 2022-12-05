//
// Created by grigoriy.senchenok on 21.12.2021.
//

#include "TESolver1DOutput.h"

function<string(double)> doublePrinter() {
    return [=](double f) -> string {
        return to_string(f);
    };
}

TESolver1DOutput<double, double> noOutput(){
    return {false, false, false, false, false, "", false, 0, 0, false, doublePrinter(), doublePrinter()};
}

//template<typename T>
TESolver1DOutput<double,double> terminal1DOutput(int NTimeSteps, function<string(double)> T2String){
    return {true, true, true, true, false, TERMINAL, false, NTimeSteps, 0, false, T2String, doublePrinter()};
}

template<typename T>
TESolver1DOutput<T,double> minimal1DOutput(const string& filePath, int NTimeSteps, function<string(T)> T2String){
    return {true, false, false, true, false, filePath, true, NTimeSteps, 50, false, T2String, doublePrinter()};
}

template<typename T>
TESolver1DOutput<T,double> maximal1DOutput(const string& filePath, int NTimeSteps, function<string(T)> T2String){
    return {true, false, false, true, false, filePath, false, NTimeSteps, 50, false, T2String, doublePrinter()};
}

template<typename T>
TESolver1DOutput<T,double> normal1DOutput(const string& filePath, int NTimeSteps, function<string(T)> T2String){
    return {true, true, true, true, true, filePath, true, NTimeSteps, 50, true, T2String, doublePrinter()};
}

template<typename T>
TESolver1DOutput<T,double> jupyter1DOutput(const string& filePath, int NTimeSteps, function<string(T)> T2String){
    return {true, true, true, false, false, filePath, true, NTimeSteps, 100, true, T2String, doublePrinter()};
}