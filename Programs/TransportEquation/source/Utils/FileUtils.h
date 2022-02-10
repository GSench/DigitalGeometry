//
// Created by grigoriy.senchenok on 10.02.2022.
//

#ifndef TRANSPORTEQUATION_FILEUTILS_H
#define TRANSPORTEQUATION_FILEUTILS_H

#include <string>

using namespace std;

bool mkdirs(const string &path);
string downDir(const string &dir, const string &sub);

#endif //TRANSPORTEQUATION_FILEUTILS_H
