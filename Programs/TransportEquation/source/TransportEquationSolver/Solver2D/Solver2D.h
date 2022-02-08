//
// Created by GSench on 14.12.2021.
//

#ifndef TRANSPORTEQUATION_SOLVER2D_H
#define TRANSPORTEQUATION_SOLVER2D_H

#include "Solver2DOutput.h"
#include "VectorField2D.h"

void SolveTransportEquation2D(Area2D &f,
                              VectorField2D &u,
                              Solver2DParams &p,
                              Solver2DOutput &output);

#endif //TRANSPORTEQUATION_SOLVER2D_H
