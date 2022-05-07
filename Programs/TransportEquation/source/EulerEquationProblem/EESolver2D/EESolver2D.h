//
// Created by grigoriy.senchenok on 21.02.2022.
//

#ifndef TRANSPORTEQUATION_EESOLVER2D_H
#define TRANSPORTEQUATION_EESOLVER2D_H

#include "../../math/Vector2D.h"
#include "EESolver2DParams.h"
#include "EESolver2DOutput.h"
#include <vector>
#include <functional>

using namespace std;

//TODO add EE solution for vertices
//void SolveEE2DVertices(vector<Vector2D>& vertices, const function<Vector2D(double)>& vc, const EESolver2DParams& params);

void EESolver2DCenterStep(Vector2D& xc, const vector<Vector2D>& vc, int it, const EESolver2DParams& params);

void SolveEE2D(vector<Vector2D>& vertices, //vertices[0] is center
               const vector<Vector2D>& vc, const vector<double>& w,
               const EESolver2DParams& params, EESolver2DOutput& out);


#endif //TRANSPORTEQUATION_EESOLVER2D_H
