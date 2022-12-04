//
// Created by grigoriy.senchenok on 18.11.2022.
//

#ifndef TRANSPORTEQUATION_VELOCITY_H
#define TRANSPORTEQUATION_VELOCITY_H

#include "../../math/Vector.h"

class Velocity {
public:
    virtual Vector direction()=0;
};


#endif //TRANSPORTEQUATION_VELOCITY_H
