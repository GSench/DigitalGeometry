//
// Created by grigoriy.senchenok on 09.12.2022.
//

#ifndef TRANSPORTEQUATION_RIEMANNPROBLEM_H
#define TRANSPORTEQUATION_RIEMANNPROBLEM_H

#include <vector>
#include "../Methods/GSQuantity.h"
#include "../Methods/GSFlow.h"

using namespace std;

GSFlow RP(const GSQuantity& QL, const GSQuantity& QR, double dt);
GSFlow CRP(const GSQuantity& QL, const GSQuantity& QR, double dt, double dx, double eps);

#endif //TRANSPORTEQUATION_RIEMANNPROBLEM_H
