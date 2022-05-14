//
// Created by grigoriy.senchenok on 21.02.2022.
//

#ifndef TRANSPORTEQUATION_EESOLVER1DPARAMS_H
#define TRANSPORTEQUATION_EESOLVER1DPARAMS_H

class EESolver1DParams {
public:
    double dt;
    int NTimeSteps;
    double dx;
    int cellCount;
};

#endif //TRANSPORTEQUATION_EESOLVER1DPARAMS_H
