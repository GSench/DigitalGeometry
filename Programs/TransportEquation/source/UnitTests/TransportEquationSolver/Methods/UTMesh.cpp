//
// Created by grigoriy.senchenok on 31.01.2023.
//

#include "UTMesh.h"

#include "../../UnitTestsLauncher.h"
#include "../../../TransportEquationSolver/Methods/Mesh.h"
#include "../../../TransportEquationSolver/Methods/RBState.h"

#include <string>
#include <iostream>

int testMeshNeighbours(){

    string testTitle = "QuantityNeighbours";
    startTestMsg(testTitle);

    Mesh<double> q0(0.5, 1.0, 0.0);
    q0.markBorder();

    Mesh<double> q1(1.5, 1.0, 1.0);
    q1.markBorder();

    q0.setNeighbour(X, R, q1);
    q1.setNeighbour(X, L, q0);

    if(
            q0.x() != 0.5 ||
            q0.next()->x() != 1.5 ||
            q0.next()->prev()->x() != 0.5
        ){
        cout << "------------- q0" << endl;
        cout << "q0 x = " << q0.x() << endl;
        cout << "q0 R x = " << q0.next()->x() << endl;
        cout << "q0 R L x = " << q0.next()->prev()->x() << endl;
        errorTestMsg(testTitle);
        return 1;
    }

    if(
            q1.x() != 1.5 ||
            q1.prev()->x() != 0.5 ||
            q1.prev()->next()->x() != 1.5
        ){
        cout << "------------- q1" << endl;
        cout << "q1 x = " << q1.x() << endl;
        cout << "q1 L x = " << q1.prev()->x() << endl;
        cout << "q1 L R x = " << q1.prev()->next()->x() << endl;
        errorTestMsg(testTitle);
        return 2;
    }

    if(
            q1.prev()->next()->xL() != 1.0 ||
            q0.next()->prev()->xR() != 1.0
        ){
        cout << "------------- border" << endl;
        cout << "q1: " << q1.prev()->next()->xL() << endl;
        cout << "q0: " << q0.next()->prev()->xR() << endl;
        errorTestMsg(testTitle);
        return 3;
    }

    successTestMsg(testTitle);
    return 0;
}

int testMeshUpdate(){

    string testTitle = "QuantityUpdate";
    startTestMsg(testTitle);

    RBState init(0.0, {
        TimeStepVelocity(Vector(1.0),Vector(1.0)),
        TimeStepVelocity(Vector(1.0),Vector(1.0))
    });
    RBState final(1.0, {
            TimeStepVelocity(Vector(1.0),Vector(1.0)),
            TimeStepVelocity(Vector(1.0),Vector(1.0))
    });
    Mesh<RBState> q(0.5, 1.0, init);
    q.setQuantity(final);
    q.apply();

    if(q.getQuantity().getVolumeFraction() != 1.0){
        cout << "VolumeFraction = "<<q.getQuantity().getVolumeFraction()<<" != 1.0"<<endl;
        errorTestMsg(testTitle);
        return 1;
    }
    successTestMsg(testTitle);
    return 0;
}