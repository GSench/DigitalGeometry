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
    vector<GSFlow> calc(Mesh<GSQuantity>& l, Mesh<GSQuantity>& r, double dt, int dirLR) const override {
        GSQuantity QL = l.getQuantity();
        GSQuantity QR = r.getQuantity();
        double eps = 1e-10;
        GSFlow result = zero(QL);
        if(QL.isSolid(eps) && QR.isGas(eps) || QR.isSolid(eps) && QL.isGas(eps))
            result = CRPnoPadding(QL, QR, dt, eps, dirLR);
        else if(QL.isDiscontinuous(eps) || QR.isDiscontinuous(eps))
            result = CRP(QL, QR, dt, l.dx(), eps, dirLR);
        else if(QL.isSolid(eps) && QR.isSolid(eps))
            result = zero(QL);
        else // gas ->|-> gas case
            result = RP(QL, QR, dt);
        return {result};
    }

};


#endif //TRANSPORTEQUATION_GASSOLIDFLOW_H
