//
// Created by grigoriy.senchenok on 18.11.2022.
//

#ifndef TRANSPORTEQUATION_VOLUMEFRACTION_H
#define TRANSPORTEQUATION_VOLUMEFRACTION_H

#include "Quantity.h"

class VolumeFraction : public Quantity {
private:
    double alfa = 0;
public:
    explicit VolumeFraction(double alfa) :
        alfa(alfa) {}

    double getAlfa() const {
        return alfa;
    }



};


#endif //TRANSPORTEQUATION_VOLUMEFRACTION_H
