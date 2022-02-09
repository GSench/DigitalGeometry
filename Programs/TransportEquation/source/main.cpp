#include "Tests/TransportEquation1Dtests.h"
#include "Tests/TransportEquation2Dtests.h"

int main() {
    test1DSolverStandard();
    Solver1Dtests();
    Solve2DRectMovementTest();
    Solve2DWhiteBearMovementTest();
    return 0;
}
