//
// Created by grigoriy.senchenok on 06.05.2022.
//

#ifndef TRANSPORTEQUATION_INTEGRATIONTOOLS_H
#define TRANSPORTEQUATION_INTEGRATIONTOOLS_H

#include <vector>
#include <functional>
#include "../../math/Vector.h"

using namespace std;

function<Vector3D(vector<Vector3D>, double)> trapezoidQuadrature();
vector<Vector3D> integrate(vector<Vector3D> f, double from, double to,
                           const function<Vector3D(vector<Vector3D>, double)>& quadrature);

#endif //TRANSPORTEQUATION_INTEGRATIONTOOLS_H
