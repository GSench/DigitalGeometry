//
// Created by grigoriy.senchenok on 18.04.2023.
//

#include "PostProcessors.h"

function<void(Mesh<GSQuantity>&)> noPostProcessGSQuantity(){
    return [=](Mesh<GSQuantity>& mesh)->void {
        return;
    };
}

function<void(Mesh<SQuantity>&)> noPostProcessSQuantity() {
    return [=](Mesh<SQuantity> &mesh) -> void {
        return;
    };
}

function<void(Mesh<GSQuantity>&)> postProcessGSQuantity(double eps) {
    return [=](Mesh<GSQuantity> &mesh) -> void {
        GSQuantity updQ = mesh.getQuantity();
        if(
            isnan(updQ.volumeFraction()) ||
            isnan(updQ.velocity()) ||
            isnan(updQ.density()) ||
            isnan(updQ.pressure())
        ){
            GSQuantity QL = mesh.prev()->getQuantity();
            GSQuantity QR = mesh.next()->getQuantity();
            updQ = (QL + QR) / (QL.volumeFraction() + QR.volumeFraction());
            if(QL.isDiscontinuous(eps) && updQ.isDiscontinuous(eps))
                updQ.applyVolumeFraction(QR.volumeFraction());
            if(QR.isDiscontinuous(eps) && updQ.isDiscontinuous(eps))
                updQ.applyVolumeFraction(QL.volumeFraction());
        }
        if (updQ.isDiscontinuous(eps)) {

        } else if (updQ.isSolid(eps)) {
            updQ.applyVolumeFraction(0.0);
        } else if (updQ.isGas(eps)) {
            updQ.applyVolumeFraction(1.0);
        }
        updQ.setSolidVelocity(mesh.prev()->getQuantity().getSolidVelocity());
        mesh.setQuantity(updQ);
    };
}

function<void(Mesh<GSQuantity>&)> postProcessGSQuantityAlfa() {
    return [=](Mesh<GSQuantity> &mesh) -> void {
        GSQuantity updQ = mesh.getQuantity();
        updQ.applyVolumeFraction(updQ.volumeFraction());
        mesh.setQuantity(updQ);
    };
}