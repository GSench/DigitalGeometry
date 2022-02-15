//
// Created by grigoriy.senchenok on 15.12.2021.
//

#ifndef TRANSPORTEQUATION_ARRAYUTILS_H
#define TRANSPORTEQUATION_ARRAYUTILS_H

#include <functional>
#include <vector>

template <typename T>
T** define2DArray(int n, int m, T val);
template <typename T>
T** define2DArray(int n, int m, std::function<T()> initializer);
template<typename T>
std::vector<T> slice(std::vector<T> const &v, int iStart, int n);

#endif //TRANSPORTEQUATION_ARRAYUTILS_H
