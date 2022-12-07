//
// Created by grigoriy.senchenok on 07.12.2022.
//

#include "TimeLogger.h"
#include <ctime>

static clock_t timePoint = 0;

void reset(){
    timePoint = clock();
}

void logTime(){
    logTime("");
}

void logTime(const string& msg){
    if(timePoint == 0){
        printf("[TimeLogger] 0.000 sec [%s]\n",msg.c_str());
        reset();
        return;
    }
    clock_t point = clock();
    double timeDif = (double)(point - timePoint)/CLOCKS_PER_SEC;
    printf("[TimeLogger] %.3f sec [%s]\n", timeDif, msg.c_str());
    reset();
}