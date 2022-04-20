//
// Created by grigoriy.senchenok on 08.02.2022.
//

#ifndef TRANSPORTEQUATION_SOLVER2DOUTPUT_H
#define TRANSPORTEQUATION_SOLVER2DOUTPUT_H

#include <fstream>
#include <iostream>
#include <vector>
#include "Area2D.h"
#include "TESolver2DParams.h"

using namespace std;

class Solver2DOutput {
private:
    bool printToFile = false;
    bool printT = true;
    ofstream resultFile;
    bool barePrint = false;
    int NTimeSteps = 100;
    int realNTimeSteps = 50;
    double printNStep = 1;

public:
    Solver2DOutput(
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

    void printHeader(const TESolver2DParams &params){
        resultFile << params.getCellCountX() << "\t" << params.getCellCountY() << "\t" << params.getDx() << endl;
        resultFile << params.getNTimeSteps() << "\t" << realNTimeSteps << "\t" << params.getDt() << endl;
    }

    void print(Area2D &f, int t){
        if(!printToFile) return;

        if(barePrint)
            if(t!=0 && t!=NTimeSteps)
                if((int)(t/printNStep) == (int)((t-1)/printNStep))
                    return;

        if(printT)
            resultFile << "t " << t << endl;

        for (int y = 0; y < f.getHeight(); y++) {
            for (int x = 0; x < f.getWidth(); x++)
                resultFile << f.get(x, y) << '\t';
            resultFile << endl;
        }
    }

    void finish(){
        if(printToFile)
            resultFile.close();
    }
};

Solver2DOutput no2DOutput();
Solver2DOutput minimal2DOutput(const string& filePath, int NTimeSteps);

#endif //TRANSPORTEQUATION_SOLVER2DOUTPUT_H
