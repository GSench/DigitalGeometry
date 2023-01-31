//
// Created by grigoriy.senchenok on 28.01.2023.
//

#include <iostream>
#include "UnitTestsLauncher.h"
#include "math/UTVector.h"
#include "TransportEquationSolver/Methods/UTRBStateFlow.h"


int launchAllUnitTests(){
    return
         testVector()
        +testVectorCreation()
        +testRBStateFlow()
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
    cout << "success: " << testName << endl;
}

void errorTestMsg(const string& testName){
    cout << "error: " << testName << endl;
}