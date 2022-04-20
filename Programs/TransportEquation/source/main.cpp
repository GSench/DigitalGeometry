#include "Tests/TransportEquation1Dtests.h"
#include "Tests/TransportEquation2Dtests.h"
#include "Tests/DigitalGeometryTests1D.h"

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
    launchTests();
    return 0;
}
