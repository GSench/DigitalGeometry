//
// Created by grigoriy.senchenok on 26.04.2022.
//

#ifndef TRANSPORTEQUATION_EESOLVER2DPARAMS_H
#define TRANSPORTEQUATION_EESOLVER2DPARAMS_H


class EESolver2DParams {
public:
    double dt;
    int NTimeSteps;

    EESolver2DParams(double dt, int nTimeSteps) : dt(dt), NTimeSteps(nTimeSteps) {}
    EESolver2DParams(int nTimeSteps, double time) : dt(time/nTimeSteps), NTimeSteps(nTimeSteps) {}
};


#endif //TRANSPORTEQUATION_EESOLVER2DPARAMS_H
