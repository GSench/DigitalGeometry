//
// Created by grigoriy.senchenok on 06.05.2022.
//

#ifndef TRANSPORTEQUATION_INTEGRATIONTOOLS_H
#define TRANSPORTEQUATION_INTEGRATIONTOOLS_H

#include <vector>
#include <functional>
#include "../../math/Vector2D.h"

using namespace std;

function<Vector2D(vector<Vector2D>, double)> trapezoidQuadrature();
vector<Vector2D> integrate(vector<Vector2D> f, double from, double to,
                           const function<Vector2D(vector<Vector2D>, double)>& quadrature);

#endif //TRANSPORTEQUATION_INTEGRATIONTOOLS_H
