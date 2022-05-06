//
// Created by grigoriy.senchenok on 26.04.2022.
//

#ifndef TRANSPORTEQUATION_EESOLVER2DPARAMS_H
#define TRANSPORTEQUATION_EESOLVER2DPARAMS_H


class EESolver2DParams {
private:
    double dt;
    int NTimeSteps;
public:
    EESolver2DParams(double dt, int nTimeSteps) : dt(dt), NTimeSteps(nTimeSteps) {}
    EESolver2DParams(int nTimeSteps, double time) : dt(time/nTimeSteps), NTimeSteps(nTimeSteps) {}

    double getDt() const {
        return dt;
    }

    int getNTimeSteps() const {
        return NTimeSteps;
    }
};


#endif //TRANSPORTEQUATION_EESOLVER2DPARAMS_H
