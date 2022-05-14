//
// Created by grigoriy.senchenok on 21.02.2022.
//

#include "DGSolver2D.h"
#include "../../EulerEquationProblem/EESolver2D/EESolver2D.h"
#include "../../math/VectorMeshTools.h"
#include "../../TransportEquationSolver/Instances/RBVectorField2D.h"
#include "../../TransportEquationSolver/Solver2D/TERBSolver2D.h"

void DG2DSolverStep(Area2D &f,
                    vector<Vector2D>& points,
                    const vector<Vector2D>& vc,
                    const vector<double>& w,
                    DGSolver2DParams p, int it){
    Vector2D xcCurr = points[0];
    EESolver2DCenterStep(points[0], vc, it, p.getParamsForEE2D());
    RBVectorField2D u(vc[it-1], xcCurr, w[it-1],
                      vc[it], points[0], w[it]);
    TERBSolver2DStep(f, u, p.getParamsForTE2D());
}

void SolveDG2D(Area2D &f,
               vector<Vector2D>& points,
               const vector<Vector2D>& vc,
               const vector<double>& w,
               DGSolver2DParams p, DGSolver2DOutput &out){
    out.print(f, points, 0);
    for(int it=1; it<=p.getParamsForEE2D().getNTimeSteps(); it++){
        DG2DSolverStep(f, points, vc, w, p, it);
        out.print(f, points, it);
    }
}