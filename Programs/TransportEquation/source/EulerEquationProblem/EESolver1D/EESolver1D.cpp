//
// Created by grigoriy.senchenok on 21.02.2022.
//

#include "EESolver1D.h"

void SolverStep(VectorField1D &v, const function<double(double)>& vc, const EESolver1DParams &p, int t){
    for(int i=0; i<p.cellCount+1; i++)
        v.set(i, vc(p.dt*t));
}

void SolveEE1D(VectorField1D &v, const function<double(double)>& vc, const EESolver1DParams &p){
    //TODO
}