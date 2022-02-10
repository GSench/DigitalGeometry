//
// Created by grigoriy.senchenok on 10.02.2022.
//

#include <iostream>

#include "../configs.h"
#include "Tests.h"
#include "../Utils/FileUtils.h"


string initTest(const string &title, const string &baseDir){
    cout << endl
         << "-----------------------------------------" << endl
         << title << endl
         << "-----------------------------------------" << endl
         << endl;
    const string &testDir = downDir(baseDir, title);
    if(mkdirs(testDir))
        return testDir;
    else return "";
}