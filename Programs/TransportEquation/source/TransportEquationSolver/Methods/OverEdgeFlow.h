//
// Created by grigoriy.senchenok on 18.11.2022.
//

#ifndef TRANSPORTEQUATION_OVEREDGEFLOW_H
#define TRANSPORTEQUATION_OVEREDGEFLOW_H

#include "Mesh.h"
#include "../../Utils/Logger.h"

template<typename Q, typename F>
class OverEdgeFlow {
public:
    virtual vector<F> calc(Mesh<Q>& l, Mesh<Q>& r, double dt, int dirLR, bool debugMode, Logger& logger) const = 0;
};


#endif //TRANSPORTEQUATION_OVEREDGEFLOW_H
