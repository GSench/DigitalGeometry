//
// Created by grigoriy.senchenok on 06.02.2023.
//

#ifndef TRANSPORTEQUATION_GASSOLIDFLOW_H
#define TRANSPORTEQUATION_GASSOLIDFLOW_H

#include "OverEdgeFlow.h"

#include "GSQuantity.h"
#include "GSFlow.h"
#include "../Tools/RiemannProblem.h"

class GasSolidFlow : public OverEdgeFlow<GSQuantity, GSFlow> {

public:
    GSFlow calc(Mesh<GSQuantity>& l, Mesh<GSQuantity>& r, double dt, int dirLR) override {
        GSQuantity QL = l.getQuantity();
        GSQuantity QR = r.getQuantity();
        double eps = 1e-10;
        if(QL.isSolid(eps) && QR.isGas(eps) || QR.isSolid(eps) && QL.isGas(eps))
            return CRPnoPadding(QL, QR, dt, eps, dirLR);
        if(QL.isDiscontinuous(eps) || QR.isDiscontinuous(eps)||QL.isSolid(eps) && QR.isGas(eps) || QR.isSolid(eps) && QL.isGas(eps))
            return CRP(QL, QR, dt, l.dx(), eps, dirLR);
        if(QL.isSolid(eps) && QR.isSolid(eps))
            return zero(QL);
        // else gas ->|-> gas case
        return RP(QL, QR, dt);
    }

};


#endif //TRANSPORTEQUATION_GASSOLIDFLOW_H
