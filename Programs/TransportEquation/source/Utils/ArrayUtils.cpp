//
// Created by grigoriy.senchenok on 15.12.2021.
//

#include "ArrayUtils.h"

#include <cstdlib>

double** define2DArray(int n, int m, double val){
    double** array2D = (double **) malloc(m * sizeof(double *));
    for(int j=0; j<m; j++) {
        array2D[j] = (double *) malloc(n * sizeof(double));
        for(int i=0; i<n; i++)
            array2D[j][i]=val;
    }
    return array2D;
}