//
// Created by grigoriy.senchenok on 18.11.2022.
//

#ifndef TRANSPORTEQUATION_VOLUMEFRACTION_H
#define TRANSPORTEQUATION_VOLUMEFRACTION_H

#include "Quantity.h"

class VolumeFraction : public Quantity {
private:
    double alfa = 0;
    double newAlfa = 0;
protected:
    void apply() override {
        alfa = newAlfa;
    }
public:
    explicit VolumeFraction(int dimensions, double alfa) :
            Quantity(dimensions), alfa(alfa), newAlfa(alfa) {}

    double getAlfa() const {
        return alfa;
    }

    void setAlfa(double alfa) {
        newAlfa = alfa;
    }

    VolumeFraction& next() override {
        return dynamic_cast<VolumeFraction&>(Quantity::next());
    }

    VolumeFraction& prev() override {
        return dynamic_cast<VolumeFraction&>(Quantity::next());
    }

};


#endif //TRANSPORTEQUATION_VOLUMEFRACTION_H
