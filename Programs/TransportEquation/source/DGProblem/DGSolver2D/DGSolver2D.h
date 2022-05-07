//
// Created by grigoriy.senchenok on 21.02.2022.
//

#ifndef TRANSPORTEQUATION_DGSOLVER2D_H
#define TRANSPORTEQUATION_DGSOLVER2D_H

#include "../../TransportEquationSolver/Instances/Area2D.h"
#include "../../TransportEquationSolver/Solver2D/TESolver2DOutput.h"
#include "DGSolver2DOutput.h"

void DG2DSolverStep(Area2D &f,
                    vector<Vector2D>& points,
                    const vector<Vector2D>& vc,
                    const vector<double>& w,
                    DGSolver2DParams p, int it);

void SolveDG2D(Area2D &f,
               vector<Vector2D>& points,
               const vector<Vector2D>& vc,
               const vector<double>& w,
               DGSolver2DParams p, DGSolver2DOutput &out);

#endif //TRANSPORTEQUATION_DGSOLVER2D_H
