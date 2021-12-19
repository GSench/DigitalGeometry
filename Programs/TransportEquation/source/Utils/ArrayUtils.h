//
// Created by grigoriy.senchenok on 15.12.2021.
//

#ifndef TRANSPORTEQUATION_ARRAYUTILS_H
#define TRANSPORTEQUATION_ARRAYUTILS_H

#include <functional>

template <typename T>
T** define2DArray(int n, int m, T val);
template <typename T>
T** define2DArray(int n, int m, std::function<T()> initializer);

#endif //TRANSPORTEQUATION_ARRAYUTILS_H
