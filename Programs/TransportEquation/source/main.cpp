#include "Tests/TransportEquation1Dtests.h"
#include "Tests/TransportEquation2Dtests.h"

void launchTests(){
    //if(!test1DSolverStandard()) return;
    if(!test1DSolverBackStandard()) return;
    Solver1DStripMovementTest();
    Solver1DStripBackMovementTest();
    return;
    Solver1Dtests();
    Solve2DRectMovementTest();
    Solve2DWhiteBearMovementTest();
}

int main() {
    launchTests();
    return 0;
}
