//
// Created by grigoriy.senchenok on 21.02.2022.
//

#ifndef TRANSPORTEQUATION_EESOLVER1D_H
#define TRANSPORTEQUATION_EESOLVER1D_H

#include "../../TransportEquationSolver/Solver1D/VectorField1D.h"
#include "EESolver1DParams.h"

void SolverStep(VectorField1D &v, const function<double(double)>& vc, const EESolver1DParams &p, int t);
void SolveEE1D(VectorField1D &v, const function<double(double)>& vc, const EESolver1DParams &p);

#endif //TRANSPORTEQUATION_EESOLVER1D_H
