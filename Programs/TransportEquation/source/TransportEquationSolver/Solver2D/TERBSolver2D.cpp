//
// Created by GSench on 14.12.2021.
//

#include "TERBSolver2D.h"
#include "../Solver1D/TERBSolver1D.h"
#include "TESolver2DParams.h"
#include "TESolver2DOutput.h"

using namespace std;

void TERBSolver2DStep(Area2D &f,
                      RBVectorField2D &u,
                      TESolver2DParams &p){
    for(int y=0; y<p.getCellCountY(); y++){
        f.projectX(y);
        u.projectX(y+p.getDx()/2);
        p.projectX();
        TERBSolverStep(f, u, p);
    }
    for(int x=0; x<p.getCellCountX(); x++){
        f.projectY(x);
        u.projectY(x+p.getDx()/2);
        p.projectY();
        TERBSolverStep(f, u, p);
    }
}

void SolveTransportEquationRB2D(Area2D &f,
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
        TERBSolver2DStep(f, rbu, p);
        output.print(f, n+1);
    }
}