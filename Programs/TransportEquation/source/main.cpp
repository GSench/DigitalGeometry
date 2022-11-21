#include <iostream>
#include "Tests/TransportEquation1Dtests.h"
#include "Tests/TransportEquation2Dtests.h"
#include "Tests/DigitalGeometryTests1D.h"
#include "Tests/EulerEquation2Dtests.h"
#include "Tests/DigitalGeometryTests2D.h"

#include "math/Vector2D.h"
#include "TransportEquationSolver/Methods/VolumeFraction.h"

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

    VolumeFraction f0(0.5, 1, 0);
    Quantity& q0 = f0;

    VolumeFraction f1(1.5, 1, 1);
    Quantity& q1 = f1;

    q0.setNeighbour(X, R, f1);
    f1.setNeighbour(X, L, q0);

    cout << "------------- f0" << endl;
    cout << "f0 = " << f0.getAlfa() << endl;
    cout << "f0 R = " << f0.next().getAlfa() << endl;
    cout << "f0 R L = " << f0.next().prev().getAlfa() << endl;

    cout << "------------- q0" << endl;
    cout << "q0 x = " << q0.x() << endl;
    cout << "q0 R x = " << q0.next().x() << endl;
    cout << "q0 R L x = " << q0.next().prev().x() << endl;

    cout << "------------- f1" << endl;
    cout << "f1 = " << f1.getAlfa() << endl;
    cout << "f1 L = " << f1.prev().getAlfa() << endl;
    cout << "f1 L R = " << f1.prev().next().getAlfa() << endl;

    cout << "------------- q1" << endl;
    cout << "q1 x = " << q1.x() << endl;
    cout << "q1 L x = " << q1.prev().x() << endl;
    cout << "q1 L R x = " << q1.prev().next().x() << endl;

    cout << "------------- border" << endl;
    cout << "q1: " << q1.prev().next().xL() << endl;
    cout << "q0: " << q0.next().prev().xR() << endl;

    return 0;
}
