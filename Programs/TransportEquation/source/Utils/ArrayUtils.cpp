//
// Created by grigoriy.senchenok on 15.12.2021.
//

#include "ArrayUtils.h"

#include <cstdlib>
#include <functional>

template <typename T>
T** define2DArray(int n, int m, T val){
    T** array2D = (T **) malloc(m * sizeof(T*));
    for(int j=0; j<m; j++) {
        array2D[j] = (T *) malloc(n * sizeof(T));
        for(int i=0; i<n; i++)
            array2D[j][i]=val;
    }
    return array2D;
}
template <typename T>
T** define2DArray(int n, int m, std::function<T()> initializer){
    T** array2D = (T **) malloc(m * sizeof(T*));
    for(int j=0; j<m; j++) {
        array2D[j] = (T *) malloc(n * sizeof(T));
        for(int i=0; i<n; i++)
            array2D[j][i]=initializer();
    }
    return array2D;
}