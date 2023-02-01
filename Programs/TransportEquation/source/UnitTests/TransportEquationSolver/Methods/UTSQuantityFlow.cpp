//
// Created by grigoriy.senchenok on 31.01.2023.
//

#include "UTSQuantityFlow.h"
#include "../../UnitTestsLauncher.h"
#include "../../../TransportEquationSolver/Methods/SQuantity.h"
#include "../../../TransportEquationSolver/Methods/SFlow.h"

#include <string>
#include <iostream>

using namespace std;

int testSQuantityFlow(){
    string testTitle = "RBStateFlow";
    startTestMsg(testTitle);

    SQuantity q(
            0.5,
            {
                TimeStepVelocity(Vector(1.0), Vector(1.0)),
                TimeStepVelocity(Vector(1.0), Vector(1.0))
            }
        );
    SFlow fL(0.3);
    SFlow fR(0.1);
    double dx = 1.0;

    SQuantity qNext = q - (fR - fL) / dx;

    if(qNext.getVolumeFraction() != 0.7){
        cout << "qNext.getVolumeFraction() != 0.7; qNext.getVolumeFraction()=" << qNext.getVolumeFraction() << endl;
        errorTestMsg(testTitle);
        return 2;
    }
    successTestMsg(testTitle);
    return 0;
}