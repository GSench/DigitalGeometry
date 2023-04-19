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
            const SQuantity& currQ,
            const vector<SFlow>& FlowsLeft,
            const vector<SFlow>& FlowsRight,
            const TESolver1DParams& p
    ) const override {
        SQuantity qResult = currQ - (FlowsRight[0] - FlowsLeft[0])/p.getDx();
        return qResult;
    }
};


#endif //TRANSPORTEQUATION_SOLIDFLOWMACHINE_H
