//
// Created by GSench on 19.01.2022.
//

#include "TESolver1DInstances.h"

C1D getCi(double dx, int i){
    return {(i+0.5)*dx, dx,i*dx,(i+1)*dx};
}

C1D inverse(const C1D &c){
    return {-c.x, c.dx, -c.xR, -c.xL};
}

F1D getFi(LineInterface& f, int i){
    return {f[i], f[i-1], f[i+1]};
}

F1D inverse(const F1D &f){
    return {f.fi, f.fiNext, f.fiPrev};
}

U1D getUi(LineInterface& u, int i){
    return {u[i], u[i+1]};
}