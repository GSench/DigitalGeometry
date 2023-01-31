#include <iostream>
#include "UnitTests/UnitTestsLauncher.h"
#include "TransportEquationSolver/Methods/TimeStepVelocity.h"

//#include "Tests/TransportEquation1Dtests.h"
/*#include "Tests/TransportEquation2Dtests.h"
#include "Tests/DigitalGeometryTests1D.h"
#include "Tests/EulerEquation2Dtests.h"
#include "Tests/DigitalGeometryTests2D.h"*/

//#include "TransportEquationSolver/Solver1D/TESolver1DOutput.h"

/*
void launchTests(){
    if(!test1DSolverStandard()) return;
    if(!test1DSolverBackStandard()) return;
    Solver1DStripMovementTest();
    Solver1DStripBackMovementTest();
    StripSinMoveTest();
    Solver1Dtests();
    Solve2DRectMovementTest();
    Solve2DWhiteBearMovementTest();
}*/

/*
void test(){

    /*
    TESolver1DOutput<double, double> output(TERMINAL, 1, 1, doublePrinter());

    output.print(q0, 0);
    cout << "q0 = " << q0.getQuantity() << endl;
    output.print(q0, 1);
    cout << "q0 = " << q0.getQuantity() << endl;
}
*/

int main() {
    TimeStepVelocity(Vector(1.0), Vector(1.0));
    return launchAllUnitTests();

}
