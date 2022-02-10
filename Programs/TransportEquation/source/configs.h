//
// Created by grigoriy.senchenok on 09.02.2022.
//

#ifndef TRANSPORTEQUATION_CONFIGS_H
#define TRANSPORTEQUATION_CONFIGS_H

#include <string>

using namespace std;

const string OUTPUT_PATH = R"(../../Output)";
const string CALCULATION_OUTPUT_PATH = OUTPUT_PATH + R"(/CalculationResults)";
const string CALCULATION_1D_OUTPUT_PATH = CALCULATION_OUTPUT_PATH + R"(/Solver1D)";
const string CALCULATION_2D_OUTPUT_PATH = CALCULATION_OUTPUT_PATH + R"(/Solver2D)";

#endif //TRANSPORTEQUATION_CONFIGS_H
