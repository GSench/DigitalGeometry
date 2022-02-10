//
// Created by GSench on 14.12.2021.
//

#include "Solver2D.h"
#include "../Solver1D/Solver1D.h"
#include "Area2D.h"
#include "VectorField2D.h"
#include "Solver2DInstances.h"
#include "Solver2DOutput.h"

using namespace std;

void SolveTransportEquation2D(Area2D &f,
                              VectorField2D &u,
                              Solver2DParams &p,
                              Solver2DOutput &output){
    output.print(f, 0);
    for (int n = 0; n < p.NTimeSteps; n++) {
        for(int y=0; y<p.cellCountY; y++){
            f.projectX(y);
            u.projectX(y);
            p.projectX();
            SolverStep(f, u, p);
        }
        for(int x=0; x<p.cellCountX; x++){
            f.projectY(x);
            u.projectY(x);
            p.projectY();
            SolverStep(f, u, p);
        }
        output.print(f, n+1);
    }
}