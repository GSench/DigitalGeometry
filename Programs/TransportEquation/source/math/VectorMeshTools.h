//
// Created by grigoriy.senchenok on 06.05.2022.
//

#ifndef TRANSPORTEQUATION_VECTORMESHTOOLS_H
#define TRANSPORTEQUATION_VECTORMESHTOOLS_H

#include <vector>
#include <functional>

using namespace std;

template <typename T>
vector<T> mesh1D(const function<T(double)>& f, double start, double finish, int n){
    vector<T> mesh(n);
    double dx = (finish-start)/(n-1);
    for(int i=0; i<n; i++)
        mesh[i] = f(start+i*dx);
    return mesh;
}

template <typename T>
vector<T> mesh1D(const function<T(double)>& f, double start, int n, double dx){
    vector<T> mesh(n);
    for(int i=0; i<n; i++)
        mesh[i] = f(start+i*dx);
    return mesh;
}


#endif //TRANSPORTEQUATION_VECTORMESHTOOLS_H
