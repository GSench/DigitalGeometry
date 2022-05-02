//
// Created by grigoriy.senchenok on 21.02.2022.
//

#ifndef TRANSPORTEQUATION_EESOLVER1D_H
#define TRANSPORTEQUATION_EESOLVER1D_H

#include "../../TransportEquationSolver/Instances/VectorField1D.h"
#include "EESolver1DParams.h"

void EESolver1DVerticeStep(double &x, const function<double(double)>& vc, const EESolver1DParams &p, int it);

void SolveEE1D(vector<double> &x, const function<double(double)>& vc, const EESolver1DParams &p);

#endif //TRANSPORTEQUATION_EESOLVER1D_H
