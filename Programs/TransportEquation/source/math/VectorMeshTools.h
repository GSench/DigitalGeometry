//
// Created by grigoriy.senchenok on 06.05.2022.
//

#ifndef TRANSPORTEQUATION_VECTORMESHTOOLS_H
#define TRANSPORTEQUATION_VECTORMESHTOOLS_H

#include <vector>
#include <functional>
#include "Vector2D.h"

using namespace std;

vector<Vector2D> mesh1D(const function<Vector2D(double)>& f, double start, double finish, int stepsCount);
vector<Vector2D> mesh1D(const function<Vector2D(double)>& f, double start, int stepsCount, double dx);


#endif //TRANSPORTEQUATION_VECTORMESHTOOLS_H
