//
// Created by grigoriy.senchenok on 18.11.2022.
//

#ifndef TRANSPORTEQUATION_CONTINUOUSRBFLOW_H
#define TRANSPORTEQUATION_CONTINUOUSRBFLOW_H


#include "Flow.h"

#include <utility>
#include "TimeStepVelocity.h"
#include "../Instances/TESolver1DInstances.h"

class ContinuousRBFlow : public Flow<double, TimeStepVelocity&> {
private:
    function<function<double(double)>(F1D f, C1D c)> FlowInterpolationFunction;
public:
    explicit ContinuousRBFlow(function<function<double(double)>(F1D, C1D)> flowInterpolationFunction)
            : FlowInterpolationFunction(std::move(flowInterpolationFunction)) {}

    double calc(Quantity<double>& l, Quantity<double>& r, double dt, Quantity<TimeStepVelocity&>& u) override {
        double x = l.xR();
        double uCurr = u.getQuantity().getU()[u.getDirection()];
        double uNext = u.getQuantity().getUNext()[u.getDirection()];
        double transportDirection = u.getQuantity().direction()[u.getDirection()];
        Quantity<double>& transportQuantity = transportDirection > 0 ? l : r;
        F1D f = {
                transportQuantity.getQuantity(),
                transportQuantity.prev()->getQuantity(),
                transportQuantity.next()->getQuantity()
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
        return dt / 2.*(uCurr*Psy(x)+uNext*Psy(x-dt*(uNext+uCurr)/2.));
    }
};


#endif //TRANSPORTEQUATION_CONTINUOUSRBFLOW_H
