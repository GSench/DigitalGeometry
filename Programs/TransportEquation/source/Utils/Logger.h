//
// Created by grigoriy.senchenok on 23.05.2023.
//

#ifndef TRANSPORTEQUATION_LOGGER_H
#define TRANSPORTEQUATION_LOGGER_H

#include <string>
#include <iostream>
#include <utility>
#include <fstream>


using namespace std;

static const int TERMINAL_OUTPUT = 0;
static const int FILE_OUTPUT = 1;

class Logger {
private:
    int mode = 0;
    ofstream file;

    void print(const string& s){
        if(mode==TERMINAL_OUTPUT)
            cout << s;
        if(mode==FILE_OUTPUT)
            file << s;
    }
public:
    Logger(int mode, const string& filepath) :
        mode(mode)
    {
        if(mode==FILE_OUTPUT){
            file.open(filepath);
        }
    }

    void log(const string& title, const string& value){
        print(title+"\t"+value+"\n");
    }

    void log(const string& msg){
        print(msg);
    }

    void finish(){
        if(mode==FILE_OUTPUT)
            file.close();
    }
};


#endif //TRANSPORTEQUATION_LOGGER_H
