//
// Created by grigoriy.senchenok on 21.02.2022.
//

#ifndef TRANSPORTEQUATION_DGSOLVER1D_H
#define TRANSPORTEQUATION_DGSOLVER1D_H

#include "../../TransportEquationSolver/Instances/Area1D.h"
#include "../../TransportEquationSolver/Instances/VectorField1D.h"
#include "../../EulerEquationProblem/EESolver1D/EESolver1DParams.h"
#include "../../TransportEquationSolver/Solver1D/TESolver1DOutput.h"

void DGSolverStep(Area1D &f, TESolver1DParams pf,
                  const function<double(double)>& vc, int t);

void SolveDG1D(Area1D &f, const TESolver1DParams& pf,
               const function<double(double)>& vc,
               TESolver1DOutput &out);

#endif //TRANSPORTEQUATION_DGSOLVER1D_H
