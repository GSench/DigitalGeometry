//
// Created by grigoriy.senchenok on 06.05.2022.
//

#include "IntegrationTools.h"

function<Vector2D(vector<Vector2D>, double)> trapezoidQuadrature(){
    return [&](vector<Vector2D> f, double dx) -> Vector2D {
        return (f[0]+f[1])/2.*dx;
    };
}

vector<Vector2D> integrate(vector<Vector2D> f, double from, double to,
                           const function<Vector2D(vector<Vector2D>, double)>& quadrature){
    vector<Vector2D> integral(f.size());
    integral[0] = Vector2D();
    double dx = (to - from) / ((int)f.size()-1);
    for(int i=1; i<f.size(); i++){
        integral[i] = integral[i-1];
        integral[i] += quadrature({f[i-1], f[i]}, dx);
    }
    return integral;
}