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
        GSFlow FR = FlowsRight[0];
        GSFlow FL = FlowsLeft[0];
        GSFlow GRMinus = FlowsRight[1];
        GSFlow GLPlus = FlowsLeft[2];
        GSQuantity QCurr = currMeshQ.getQuantity();
        GSQuantity QNext = QCurr - ((FR - GRMinus) - (FL + GLPlus))/p.getDx();
        GSFlow totalGasFlow = (FL - FR)/p.getDx();
        GSFlow totalSolidFlow = (GRMinus + GLPlus)/p.getDx();
        return QNext;
    }
};

#endif //TRANSPORTEQUATION_GASSOLIDFLOWMACHINE_H
