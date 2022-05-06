//
// Created by grigoriy.senchenok on 21.02.2022.
//

#include "EESolver2D.h"
#include "../Tools/IntegrationTools.h"

void EESolver2DCenterStep(Vector2D& xc, const vector<Vector2D>& vc, int it, const EESolver2DParams& params){
    if(it<=0) return;
    xc+=trapezoidQuadrature()({vc[it-1], vc[it]}, params.dt);
}

void SolveEE2D(vector<Vector2D>& vertices, //vertices[0] is center
               const vector<Vector2D>& vc, const function<double(double)>& w,
               const EESolver2DParams& params, EESolver2DOutput& out){
    out.print(vertices, 0);
    for(int it=1; it<=params.NTimeSteps; it++){
        EESolver2DCenterStep(vertices[0], vc, it, params);
        //TODO solve for vertices here
        out.print(vertices, it);
    }
}

