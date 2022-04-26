//
// Created by grigoriy.senchenok on 21.02.2022.
//

#include "DGSolver1D.h"
#include "../../EulerEquationProblem/EESolver1D/EESolver1D.h"
#include "../../TransportEquationSolver/Solver1D/TESolver1D.h"
#include "../../math/MathUtils.h"


void DGSolverStep(Area1D &f, TESolver1DParams pf,
                  VectorField1D &u, const EESolver1DParams &pu,
                  const function<double(double)>& vc, int t){
    EESolverStep(u, fMoveX(vc, pu.dt / 2), pu, t);
    TESolverStep(f, u, pf);
}

void SolveDG1D(Area1D &f, const TESolver1DParams& pf,
               VectorField1D& u, const EESolver1DParams &pu,
               const function<double(double)>& vc,
               TESolver1DOutput &out){
    out.print(f, 0, pf.getDx());
    for (int n = 0; n < pf.getNTimeSteps(); n++) {
        DGSolverStep(f, pf, u, pu, vc, n);
        out.print(f, n+1, pf.getDx());
    }
}