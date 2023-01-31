//
// Created by grigoriy.senchenok on 31.01.2023.
//

#include "UTRBStateFlow.h"
#include "../../UnitTestsLauncher.h"
#include "../../../TransportEquationSolver/Methods/RBState.h"
#include "../../../TransportEquationSolver/Methods/RBFlow.h"

#include <string>
#include <iostream>

using namespace std;

int testRBStateFlow(){
    string testTitle = "RBStateFlow";
    startTestMsg(testTitle);

    RBState q(
            0.5,
            {
                TimeStepVelocity(Vector(1.0), Vector(1.0)),
                TimeStepVelocity(Vector(1.0), Vector(1.0))
            }
        );
    RBFlow fL(0.3);
    RBFlow fR(0.1);
    double dx = 1.0;

    RBState qNext = q - (fR-fL)/dx;

    if(qNext.getVolumeFraction() != 0.7){
        cout << "qNext.getVolumeFraction() != 0.7; qNext.getVolumeFraction()=" << qNext.getVolumeFraction() << endl;
        errorTestMsg(testTitle);
        return 2;
    }
    successTestMsg(testTitle);
    return 0;
}