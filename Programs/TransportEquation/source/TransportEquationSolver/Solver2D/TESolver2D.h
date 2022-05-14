//
// Created by GSench on 14.12.2021.
//

#ifndef TRANSPORTEQUATION_TESOLVER2D_H
#define TRANSPORTEQUATION_TESOLVER2D_H

#include "TESolver2DOutput.h"
#include "../Instances/VectorField2D.h"

void TESolver2DStep(Area2D &f,
                    VectorField2D &u,
                    TESolver2DParams &p);

void SolveTransportEquation2D(Area2D &f,
                              VectorField2D &u,
                              TESolver2DParams &p,
                              TESolver2DOutput &output);

#endif //TRANSPORTEQUATION_TESOLVER2D_H
