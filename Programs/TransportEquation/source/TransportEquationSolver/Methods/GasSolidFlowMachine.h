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
            const TESolver1DParams& p,
            bool debugMode,
            Logger& logger
    ) const override {
        GSFlow FR = FlowsRight[0];
        GSFlow FL = FlowsLeft[0];
        GSFlow GRMinus = FlowsRight[1];
        GSFlow GLPlus = FlowsLeft[2];
        GSQuantity QCurr = currMeshQ.getQuantity();
        GSQuantity QNext = QCurr - ((FR - GRMinus) - (FL + GLPlus))/p.getDx();
        GSFlow totalGasFlow = (FL - FR)/p.getDx();
        GSFlow totalSolidFlow = (GRMinus + GLPlus)/p.getDx();
        if(debugMode){
            logger.log("FINAL CELL FLOWS");
            logger.log("Q current", QCurr.toString());
            logger.log("FL", FR.toString());
            logger.log("FR", FR.toString());
            logger.log("GR-", GRMinus.toString());
            logger.log("GL+", GLPlus.toString());
            logger.log("Q next", QNext.toString());
        }
        return QNext;
    }
};

#endif //TRANSPORTEQUATION_GASSOLIDFLOWMACHINE_H
