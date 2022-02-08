//
// Created by GSench on 20.01.2022.
//

#include "VectorField1D.h"
#include <vector>

using namespace std;

VectorField1D getStaticVF1D(double uStatic, int size){
    return {
            [=](int xi)->double{
                return uStatic;
            }, size
    };
}