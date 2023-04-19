//
// Created by grigoriy.senchenok on 19.04.2023.
//

#ifndef TRANSPORTEQUATION_GASSOLIDFLOWMACHINE_H
#define TRANSPORTEQUATION_GASSOLIDFLOWMACHINE_H

#include "GSQuantity.h"
#include "GSFlow.h"
#include "FlowMachine.h"

class GasSolidFlowMachine : public FlowMachine<GSQuantity, GSFlow> {
public:
    GSQuantity calculateCell(
            const Mesh<GSQuantity>& currMeshQ,
            const vector<GSFlow>& FlowsLeft,
            const vector<GSFlow>& FlowsRight,
            const TESolver1DParams& p
    ) const override {
        GSQuantity qResult = currMeshQ.getQuantity() - (FlowsRight[0] - FlowsLeft[0])/p.getDx();
        return qResult;
    }
};

#endif //TRANSPORTEQUATION_GASSOLIDFLOWMACHINE_H
