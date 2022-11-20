#include <iostream>
#include "Tests/TransportEquation1Dtests.h"
#include "Tests/TransportEquation2Dtests.h"
#include "Tests/DigitalGeometryTests1D.h"
#include "Tests/EulerEquation2Dtests.h"
#include "Tests/DigitalGeometryTests2D.h"

#include "math/Vector2D.h"

void launchTests(){
    if(!test1DSolverStandard()) return;
    if(!test1DSolverBackStandard()) return;
    Solver1DStripMovementTest();
    Solver1DStripBackMovementTest();
    StripSinMoveTest();
    Solver1Dtests();
    Solve2DRectMovementTest();
    Solve2DWhiteBearMovementTest();
}

int main() {
    //PlusRotateTest();
    Vector2D v2(1,2);
    Vector3D& v3 = v2;
    cout<<v3.dim()<<endl;
    return 0;
}
