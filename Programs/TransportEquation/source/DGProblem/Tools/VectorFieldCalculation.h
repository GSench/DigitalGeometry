//
// Created by gsench on 02.05.22.
//

#ifndef TRANSPORTEQUATION_VECTORFIELDCALCULATION_H
#define TRANSPORTEQUATION_VECTORFIELDCALCULATION_H

#include "../../TransportEquationSolver/Instances/VectorField1D.h"
#include "../../TransportEquationSolver/Instances/VectorField2D.h"

VectorField1D generateVectorField1D(double vc, int cellCount);

VectorField2D generateVectorField2D(Vector2D v0, double w, Vector2D xc, int cellCountX, int cellCountY);

#endif //TRANSPORTEQUATION_VECTORFIELDCALCULATION_H
