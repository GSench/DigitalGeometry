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
GSFlow CRPnoPadding(const GSQuantity& QL, const GSQuantity& QR, double dt, double eps, int dirLR);
GSFlow CRP(const GSQuantity& QL, const GSQuantity& QR, double dt, double dx, double eps, int dirLR);
GSFlow CRPMastering(const GSQuantity& QL, const GSQuantity& QR, double dt, double dx, double eps, int dirLR);

#endif //TRANSPORTEQUATION_RIEMANNPROBLEM_H
