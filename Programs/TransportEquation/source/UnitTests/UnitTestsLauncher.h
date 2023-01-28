//
// Created by grigoriy.senchenok on 28.01.2023.
//

#ifndef TRANSPORTEQUATION_UNITTESTSLAUNCHER_H
#define TRANSPORTEQUATION_UNITTESTSLAUNCHER_H

#include <string>

using namespace std;

int launchAllUnitTests();
void startTestMsg(const string& testName);
void successTestMsg(const string& testName);
void errorTestMsg(const string& testName);

#endif //TRANSPORTEQUATION_UNITTESTSLAUNCHER_H
