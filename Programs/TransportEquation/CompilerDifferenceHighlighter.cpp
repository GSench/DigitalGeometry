//
// Created by GSench on 14.12.2021.
// This source highlights differences between VS compiler and CLion compiler
#include <math.h>

int main1() {
    double a = 1.9212627763571921;
    double b = tanh(a);
    double res1 = 1 + b;
    double res2 = 1 + tanh(a);
    // res1 differs from res2, despite it is mathematically identical
    return 0;
}
