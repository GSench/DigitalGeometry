//
// Created by grigoriy.senchenok on 09.12.2022.
//

#ifndef TRANSPORTEQUATION_RIEMANNPROBLEM_H
#define TRANSPORTEQUATION_RIEMANNPROBLEM_H

#include <vector>
#include "../Methods/GRBState.h"

using namespace std;

pair<double, double> RPWaves(double ul, double ur, double al, double ar);
double RPRBWave(double ul, double al, double vs);


#endif //TRANSPORTEQUATION_RIEMANNPROBLEM_H
