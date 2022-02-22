//
// Created by grigoriy.senchenok on 21.02.2022.
//

#ifndef TRANSPORTEQUATION_EESOLVER1DINSTANCES_H
#define TRANSPORTEQUATION_EESOLVER1DINSTANCES_H

class EESolver1DParams {
public:
    double dt;
    double areaLength;
    int cellCount;
    int NTimeSteps;
    double dx;
};

#endif //TRANSPORTEQUATION_EESOLVER1DINSTANCES_H
