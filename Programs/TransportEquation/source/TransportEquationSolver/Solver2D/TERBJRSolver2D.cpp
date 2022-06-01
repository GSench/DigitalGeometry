//
// Created by GSench on 14.12.2021.
//

#include "TERBJRSolver2D.h"
#include "../Solver1D/TERBJRSolver1D.h"
#include "TESolver2DParams.h"
#include "TESolver2DOutput.h"

using namespace std;

void TERBJRSolver2DStep(Area2D &f,
                      RBVectorField2D &u,
                      TESolver2DParams &p){
    for(int y=0; y<p.getCellCountY(); y++){
        f.projectX(y);
        u.projectX((y+0.5)*p.getDx());
        p.projectX();
        TERBJRSolverStep(f, u, p);
    }
    for(int x=0; x<p.getCellCountX(); x++){
        f.projectY(x);
        u.projectY((x+0.5)*p.getDx());
        p.projectY();
        TERBJRSolverStep(f, u, p);
    }
}

void SolveTransportEquationRBJR2D(Area2D &f,
                                vector<Vector2D> &vc,
                                vector<Vector2D> &xc,
                                vector<double>& omega,
                                TESolver2DParams &p,
                                TESolver2DOutput &output){
    output.print(f, 0);
    for (int n = 0; n < p.getNTimeSteps(); n++) {
        RBVectorField2D rbu(
                vc[n], xc[n], omega[n],
                vc[n+1], vc[n+1], omega[n+1]
                );
        TERBJRSolver2DStep(f, rbu, p);
        output.print(f, n+1);
    }
}