//
// Created by grigoriy.senchenok on 09.12.2022.
//

#ifndef TRANSPORTEQUATION_RIEMANNPROBLEM_H
#define TRANSPORTEQUATION_RIEMANNPROBLEM_H

#include <vector>
#include "../Methods/GSQuantity.h"
#include "../Methods/GSFlow.h"

using namespace std;

pair<double, double> RPWaves(double ul, double ur, double al, double ar);
double RPRBWave(double ul, double al, double vs);
GSFlow RP(const GSQuantity& QL, const GSQuantity& QR, double dt);

#endif //TRANSPORTEQUATION_RIEMANNPROBLEM_H
