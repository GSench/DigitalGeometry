//
// Created by grigoriy.senchenok on 28.01.2023.
//

#include <iostream>
#include "UnitTestsLauncher.h"
#include "math/UTVector.h"
#include "TransportEquationSolver/Methods/UTSQuantityFlow.h"
#include "TransportEquationSolver/Methods/UTMesh.h"


int launchAllUnitTests(){
    return
            testVector()
            + testVectorCreation()
            + testSQuantityFlow()
            + testMeshNeighbours()
            + testMeshUpdate()
        //+someOtherTest()
    ;
}

void cut(){
    cout << "----------------------" << endl;
}

void startTestMsg(const string& testName){
    cut();
    cout << "testing: " << testName << endl;
}

void successTestMsg(const string& testName){
    cout << "SUCCESS: " << testName << endl;
}

void errorTestMsg(const string& testName){
    cout << "00000000000000000000000 ERROR: " << testName << endl;
}