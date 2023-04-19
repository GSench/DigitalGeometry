//
// Created by grigoriy.senchenok on 19.04.2023.
//

#ifndef TRANSPORTEQUATION_FLOWMACHINE_H
#define TRANSPORTEQUATION_FLOWMACHINE_H

#include <vector>
#include "../Solver1D/TESolver1DParams.h"

using namespace std;

template<typename Q, typename F>
class FlowMachine {
public:
    virtual Q calculateCell(const Mesh<Q>& currMeshQ, const vector<F>& FlowsLeft, const vector<F>& FlowsRight, const TESolver1DParams& p) const = 0;
};


#endif //TRANSPORTEQUATION_FLOWMACHINE_H
