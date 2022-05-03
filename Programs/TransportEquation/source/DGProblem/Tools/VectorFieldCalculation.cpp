//
// Created by gsench on 02.05.22.
//

#include "VectorFieldCalculation.h"
#include "../../TransportEquationSolver/Instances/RBVectorField1D.h"


VectorField1D generateVectorField1D(double vc, int cellCount){
    return getStaticVF1D(vc, cellCount+1);
}

VectorField2D generateVectorField2D(Vector2D v0, double w, Vector2D xc, int cellCountX, int cellCountY){
    //TODO
    return getStaticVF2D(v0, cellCountX+1, cellCountY+1);
}

