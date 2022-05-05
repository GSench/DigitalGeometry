//
// Created by grigoriy.senchenok on 21.02.2022.
//

#include "DGSolver1D.h"
#include "../../TransportEquationSolver/Solver1D/TERBSolver1D.h"
#include "../../math/MathUtils.h"


void DGSolverStep(Area1D &f, TESolver1DParams pf,
                  const function<double(double)>& vc, int t){
    RBVectorField1D u(vc(pf.getDt() * t), vc(pf.getDt() * (t+1)));
    TERBSolverStep(f, u, pf);
}

void SolveDG1D(Area1D &f, const TESolver1DParams& pf,
               const function<double(double)>& vc,
               TESolver1DOutput &out){
    out.print(f, 0, pf.getDx());
    for (int n = 0; n < pf.getNTimeSteps(); n++) {
        DGSolverStep(f, pf, vc, n);
        out.print(f, n+1, pf.getDx());
    }
}