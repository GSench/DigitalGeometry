//
// Created by gsench on 02.05.22.
//

#ifndef TRANSPORTEQUATION_EESOLVER2DOUTPUT_H
#define TRANSPORTEQUATION_EESOLVER2DOUTPUT_H

#include <fstream>
#include <iostream>
#include <vector>
#include "EESolver2DParams.h"
#include "../../math/Vector2D.h"

using namespace std;

class EESolver2DOutput {
private:
    bool printToFile = false;
    bool printT = true;
    ofstream resultFile;
    bool barePrint = false;
    int NTimeSteps = 100;
    int realNTimeSteps = 50;
    double printNStep = 1;

public:
    EESolver2DOutput(
            bool printToFile,
            bool printT,
            const string& resultFilePath,
            bool barePrint,
            int NTimeSteps,
            int maxFrames
    ) :
            printToFile(printToFile),
            printT(printT),
            barePrint(barePrint && (maxFrames < NTimeSteps)),
            NTimeSteps(NTimeSteps),
            realNTimeSteps(barePrint ? min(maxFrames, NTimeSteps) : NTimeSteps),
            printNStep( (double)NTimeSteps / min(maxFrames, NTimeSteps))
    {
        if(printToFile){
            resultFile.open(resultFilePath);
        }
    }

    void printHeader(const EESolver2DParams &params){
        resultFile << params.getNTimeSteps() << "\t" << realNTimeSteps << "\t" << params.getDt() << endl;
    }

    void print(const vector<Vector2D>& points, int t){
        if(!printToFile) return;

        if(barePrint)
            if(t!=0 && t!=NTimeSteps)
                if((int)(t/printNStep) == (int)((t-1)/printNStep))
                    return;

        if(printT)
            resultFile << "t " << t << endl;

        for(Vector2D point: points)
            resultFile << point.x << '\t' << point.y << endl;
    }

    void finish(){
        if(printToFile)
            resultFile.close();
    }
};

EESolver2DOutput no2DOutputEE();
EESolver2DOutput minimal2DOutputEE(const string& filePath, int NTimeSteps);


#endif //TRANSPORTEQUATION_EESOLVER2DOUTPUT_H
