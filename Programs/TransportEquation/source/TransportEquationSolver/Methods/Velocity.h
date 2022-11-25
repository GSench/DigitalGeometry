//
// Created by grigoriy.senchenok on 18.11.2022.
//

#ifndef TRANSPORTEQUATION_VELOCITY_H
#define TRANSPORTEQUATION_VELOCITY_H

#include "../../math/Vector3D.h"

class Velocity {
public:
    virtual Vector3D direction()=0;
};


#endif //TRANSPORTEQUATION_VELOCITY_H
