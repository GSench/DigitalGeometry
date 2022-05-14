//
// Created by grigoriy.senchenok on 06.05.2022.
//

#ifndef TRANSPORTEQUATION_RBVECTORFIELD2D_H
#define TRANSPORTEQUATION_RBVECTORFIELD2D_H

#include <vector>
#include "RBVectorField1D.h"
#include "../../math/Vector2D.h"

using namespace std;

class RBVectorField2D : public RBVectorField1D {
private:
    Vector2D vc;
    Vector2D xc;
    double omega;
    Vector2D vcNext;
    Vector2D xcNext;
    double omegaNext;
public:
    RBVectorField2D(const Vector2D &vc, const Vector2D &xc, double omega,
                    const Vector2D &vcNext, const Vector2D &xcNext, double omegaNext) :
                    RBVectorField1D(vc.x, vcNext.x),
                    vc(vc), xc(xc), omega(omega),
                    vcNext(vcNext), xcNext(xcNext), omegaNext(omegaNext)
                    {}

    void projectX(double y){
        u = vc.x + omega * (y-xc.y);
        uNext = vcNext.x + omegaNext * (y-xcNext.y);
    }

    void projectY(double x){
        u = vc.y + omega * (xc.x-x);
        uNext = vcNext.y + omegaNext * (xcNext.x-x);
    }
};


#endif //TRANSPORTEQUATION_RBVECTORFIELD2D_H
