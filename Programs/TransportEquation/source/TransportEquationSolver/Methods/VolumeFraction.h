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

    explicit VolumeFraction(Vector3D& cellPos, Vector3D& cellSize, double alfa):
        Quantity(cellPos, cellSize),
        alfa(alfa),
        newAlfa(alfa)
    {}

    explicit VolumeFraction(Vector3D& cellPos, double dx, double alfa): // square, cube
        Quantity(cellPos, dx),
        alfa(alfa),
        newAlfa(alfa)
    {}

    explicit VolumeFraction(double cellPos, double dx, double alfa): // 1D
        Quantity(cellPos, dx),
        alfa(alfa),
        newAlfa(alfa)
    {}

    double getAlfa() const {
        return alfa;
    }

    void setAlfa(double a) {
        newAlfa = a;
    }

    VolumeFraction& next() override {
        return dynamic_cast<VolumeFraction&>(Quantity::next());
    }

    VolumeFraction& prev() override {
        return dynamic_cast<VolumeFraction&>(Quantity::prev());
    }

};


#endif //TRANSPORTEQUATION_VOLUMEFRACTION_H
