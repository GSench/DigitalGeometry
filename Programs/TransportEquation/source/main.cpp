#include "Tests/TransportEquation1Dtests.h"
#include "Tests/TransportEquation2Dtests.h"

void launchTests(){
    if(!test1DSolverStandard()) return;
    Solver1DStripMovementTest();
    Solver1DStripBackMovementTest();
    Solver1Dtests();
    Solve2DRectMovementTest();
    Solve2DWhiteBearMovementTest();
}

int main() {
    launchTests();
    return 0;
}
