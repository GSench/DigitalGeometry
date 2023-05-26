//
// Created by grigoriy.senchenok on 19.04.2023.
//

#ifndef TRANSPORTEQUATION_SOLIDFLOWMACHINE_H
#define TRANSPORTEQUATION_SOLIDFLOWMACHINE_H

#include "SQuantity.h"
#include "SFlow.h"
#include "FlowMachine.h"

class SolidFlowMachine : public FlowMachine<SQuantity, SFlow> {
public:
    SQuantity calculateCell(
            const Mesh<SQuantity>& currMeshQ,
            const vector<SFlow>& FlowsLeft,
            const vector<SFlow>& FlowsRight,
            const TESolver1DParams& p,
            bool debugMode,
            Logger& logger
    ) const override {
        SQuantity qResult = currMeshQ.getQuantity() - (FlowsRight[0] - FlowsLeft[0])/p.getDx();
        return qResult;
    }
};


#endif //TRANSPORTEQUATION_SOLIDFLOWMACHINE_H
