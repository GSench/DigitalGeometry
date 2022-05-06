//
// Created by GSench on 14.12.2021.
//

#include "TESolver2D.h"
#include "../Solver1D/TESolver1D.h"
#include "../Instances/Area2D.h"
#include "../Instances/VectorField2D.h"
#include "TESolver2DParams.h"
#include "TESolver2DOutput.h"

using namespace std;

void TESolver2DStep(Area2D &f,
                    VectorField2D &u,
                    TESolver2DParams &p){
    for(int y=0; y<p.getCellCountY(); y++){
        f.projectX(y);
        u.projectX(y);
        p.projectX();
        TESolverStep(f, u, p);
    }
    for(int x=0; x<p.getCellCountX(); x++){
        f.projectY(x);
        u.projectY(x);
        p.projectY();
        TESolverStep(f, u, p);
    }
}

void SolveTransportEquation2D(Area2D &f,
                              VectorField2D &u,
                              TESolver2DParams &p,
                              TESolver2DOutput &output){
    output.print(f, 0);
    for (int n = 0; n < p.getNTimeSteps(); n++) {
        TESolver2DStep(f, u, p);
        output.print(f, n+1);
    }
}