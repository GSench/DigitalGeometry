//
// Created by grigoriy.senchenok on 21.02.2022.
//

#ifndef TRANSPORTEQUATION_DGSOLVER1D_H
#define TRANSPORTEQUATION_DGSOLVER1D_H

#include "../../TransportEquationSolver/Solver1D/Area1D.h"
#include "../../TransportEquationSolver/Solver1D/VectorField1D.h"
#include "../../EulerEquationProblem/EESolver1D/EESolver1DInstances.h"
#include "../../TransportEquationSolver/Solver1D/Solver1DOutput.h"

void SolverStep(Area1D &f, TESolver1DParams pf,
                VectorField1D &u, const EESolver1DParams &pu,
                const function<double(double)>& vc, int t);

void SolveDG1D(Area1D &f, const TESolver1DParams& pf,
               VectorField1D& u, const EESolver1DParams &pu,
               const function<double(double)>& vc,
               Solver1DOutput &out);

#endif //TRANSPORTEQUATION_DGSOLVER1D_H
