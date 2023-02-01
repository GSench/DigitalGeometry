//
// Created by grigoriy.senchenok on 18.11.2022.
//

#ifndef TRANSPORTEQUATION_CONTINUOUSRBFLOW_H
#define TRANSPORTEQUATION_CONTINUOUSRBFLOW_H


#include "OverEdgeFlow.h"

#include <utility>
#include "TimeStepVelocity.h"
#include "../Instances/TESolver1DInstances.h"
#include "SQuantity.h"
#include "SFlow.h"
#include "../../math/MathUtils.h"

class ContinuousRBFlow : public OverEdgeFlow<SQuantity, SFlow> {
private:
    function<function<double(double)>(F1D f, C1D c)> FlowInterpolationFunction;
public:
    explicit ContinuousRBFlow(function<function<double(double)>(F1D, C1D)> flowInterpolationFunction)
            : FlowInterpolationFunction(std::move(flowInterpolationFunction)) {}

    SFlow calc(Mesh<SQuantity>& l, Mesh<SQuantity>& r, double dt) override {
        double x = l.xR();
        double uCurr = l.getQuantity().currVelocityDir(l.getDirection(), R);
        double uNext = l.getQuantity().nextVelocityDir(l.getDirection(), R);
        double transportDirection = l.getQuantity().velocity(l.getDirection(), R).direction()[l.getDirection()];
        Mesh<SQuantity>& transportQuantity = transportDirection > 0 ? l : r;
        F1D f = {
                transportQuantity.getQuantity().getVolumeFraction(),
                transportQuantity.prev()->getQuantity().getVolumeFraction(),
                transportQuantity.next()->getQuantity().getVolumeFraction()
        };
        C1D c = {
                transportQuantity.x(),
                transportQuantity.dx(),
                transportQuantity.xL(),
                transportQuantity.xR()
        };
        if(transportDirection<0){
            f = inverse(f);
            c = inverse(c);
        }
        function<double(double)> Psy = FlowInterpolationFunction(f, c);
        if(transportDirection<0) Psy = fInverseX(Psy);
        return SFlow(dt / 2. * (uCurr * Psy(x) + uNext * Psy(x - dt * (uNext + uCurr) / 2.)));
    }
};


#endif //TRANSPORTEQUATION_CONTINUOUSRBFLOW_H
