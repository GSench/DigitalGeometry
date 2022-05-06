//
// Created by grigoriy.senchenok on 06.05.2022.
//

#include "VectorMeshTools.h"

vector<Vector2D> mesh1D(const function<Vector2D(double)>& f, double start, double finish, int n){
    vector<Vector2D> mesh(n);
    double dx = (finish-start)/(n-1);
    for(int i=0; i<n; i++)
        mesh[i] = f(start+i*dx);
    return mesh;
}

vector<Vector2D> mesh1D(const function<Vector2D(double)>& f, double start, int n, double dx){
    vector<Vector2D> mesh(n);
    for(int i=0; i<n; i++)
        mesh[i] = f(start+i*dx);
    return mesh;
}

