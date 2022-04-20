//
// Created by grigoriy.senchenok on 21.02.2022.
//

#include "DGSolver1D.h"
#include "../../EulerEquationProblem/EESolver1D/EESolver1D.h"
#include "../../TransportEquationSolver/Solver1D/Solver1D.h"
#include "../../math/MathUtils.h"


void SolverStep(Area1D &f, TESolver1DParams pf,
                VectorField1D &u, const EESolver1DParams &pu,
                const function<double(double)>& vc, int t){
    SolverStep(u, fMoveX(vc, pu.dt/2), pu, t);
    SolverStep(f, u, pf);
}

void SolveDG1D(Area1D &f, const TESolver1DParams& pf,
               VectorField1D& u, const EESolver1DParams &pu,
               const function<double(double)>& vc,
               Solver1DOutput &out){
    out.print(f, 0, pf.getDx());
    for (int n = 0; n < pf.getNTimeSteps(); n++) {
        SolverStep(f, pf, u, pu, vc, n);
        out.print(f, n+1, pf.getDx());
    }
}