//
// Created by grigoriy.senchenok on 10.02.2022.
//

#include "FileUtils.h"

/*
#if __cplusplus < 201703L // If the version of C++ is less than 17
#include <experimental/filesystem>
// It was still in the experimental:: namespace
namespace fs = std::experimental::filesystem;
#else
#include <filesystem>
namespace fs = std::filesystem;
#endif

bool mkdirs(const string &path){
    return fs::create_directories(path);
}

If you are using cmake, add the following line to CMakeLists.txt:
link_libraries(stdc++fs)
So that cmake can link against the corresponding library.
Haven't tried yet.
 */

string downDir(const string &dir, const string &sub){
    return dir + "/" + sub;
}

bool mkdirs(const string &path){
    //TODO recursively create folders of the path
    //maybe call Python?
    return true;
}