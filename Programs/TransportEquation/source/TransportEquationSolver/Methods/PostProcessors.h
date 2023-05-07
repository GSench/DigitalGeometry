//
// Created by grigoriy.senchenok on 18.04.2023.
//

#ifndef TRANSPORTEQUATION_POSTPROCESSORS_H
#define TRANSPORTEQUATION_POSTPROCESSORS_H

#include "Mesh.h"
#include "GSQuantity.h"
#include "SQuantity.h"

function<void(Mesh<GSQuantity>&)> noPostProcessGSQuantity();

function<void(Mesh<SQuantity>&)> noPostProcessSQuantity();

function<void(Mesh<GSQuantity>&)> postProcessGSQuantity(double eps);

function<void(Mesh<GSQuantity>&)> postProcessGSQuantityAlfa();


#endif //TRANSPORTEQUATION_POSTPROCESSORS_H
