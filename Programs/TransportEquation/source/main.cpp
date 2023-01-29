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

    Quantity<double> q0(0.5, 1, 0);
    q0.markBorder();

    Quantity<double> q1(1.5, 1, 1);
    q1.markBorder();

    q0.setNeighbour(X, R, q1);
    q1.setNeighbour(X, L, q0);

    cout << "------------- q0" << endl;
    cout << "q0 x = " << q0.x() << endl;
    cout << "q0 R x = " << q0.next()->x() << endl;
    cout << "q0 R L x = " << q0.next()->prev()->x() << endl;

    cout << "------------- q1" << endl;
    cout << "q1 x = " << q1.x() << endl;
    cout << "q1 L x = " << q1.prev()->x() << endl;
    cout << "q1 L R x = " << q1.prev()->next()->x() << endl;

    cout << "------------- border" << endl;
    cout << "q1: " << q1.prev()->next()->xL() << endl;
    cout << "q0: " << q0.next()->prev()->xR() << endl;

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
