//
// Created by grigoriy.senchenok on 06.05.2022.
//

#include "IntegrationTools.h"

function<Vector3D(vector<Vector3D>, double)> trapezoidQuadrature(){
    return [&](vector<Vector3D> f, double dx) -> Vector3D {
        return (f[0]+f[1])/2.*dx;
    };
}

vector<Vector3D> integrate(vector<Vector3D> f, double from, double to,
                           const function<Vector3D(vector<Vector3D>, double)>& quadrature){
    vector<Vector3D> integral(f.size());
    integral[0] = Vector3D();
    double dx = (to - from) / ((int)f.size()-1);
    for(int i=1; i<f.size(); i++){
        integral[i] = integral[i-1];
        integral[i] += quadrature({f[i-1], f[i]}, dx);
    }
    return integral;
}