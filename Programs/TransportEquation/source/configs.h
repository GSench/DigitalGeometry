//
// Created by grigoriy.senchenok on 09.02.2022.
//

#ifndef TRANSPORTEQUATION_CONFIGS_H
#define TRANSPORTEQUATION_CONFIGS_H

#include <string>

using namespace std;

const string OUTPUT_PATH = R"(../../Output)";
const string CALCULATION_OUTPUT_PATH = OUTPUT_PATH + R"(/CalculationResults)";
const string CALCULATION_TE1D_OUTPUT_PATH = CALCULATION_OUTPUT_PATH + R"(/TransportEquation/Solver1D)";
const string CALCULATION_TE2D_OUTPUT_PATH = CALCULATION_OUTPUT_PATH + R"(/TransportEquation/Solver2D)";
const string CALCULATION_EE1D_OUTPUT_PATH = CALCULATION_OUTPUT_PATH + R"(/EulerEquation/Solver1D)";
const string CALCULATION_EE2D_OUTPUT_PATH = CALCULATION_OUTPUT_PATH + R"(/EulerEquation/Solver2D)";
const string CALCULATION_DG1D_OUTPUT_PATH = CALCULATION_OUTPUT_PATH + R"(/DigitalGeometry/Solver1D)";
const string CALCULATION_DG2D_OUTPUT_PATH = CALCULATION_OUTPUT_PATH + R"(/DigitalGeometry/Solver2D)";

#endif //TRANSPORTEQUATION_CONFIGS_H
