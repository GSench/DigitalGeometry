//
// Created by grigoriy.senchenok on 18.11.2022.
//

#ifndef TRANSPORTEQUATION_OVEREDGEFLOW_H
#define TRANSPORTEQUATION_OVEREDGEFLOW_H

#include "Mesh.h"

template<typename Q, typename F>
class OverEdgeFlow {
public:
    virtual F calc(Mesh<Q>& l, Mesh<Q>& r, double dt, double dx) = 0;
};


#endif //TRANSPORTEQUATION_OVEREDGEFLOW_H
