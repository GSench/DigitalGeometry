//
// Created by grigoriy.senchenok on 21.12.2021.
//

#ifndef TRANSPORTEQUATION_TESOLVER1DOUTPUT_H
#define TRANSPORTEQUATION_TESOLVER1DOUTPUT_H

#include <fstream>
#include <iostream>
#include <vector>
#include "../Instances/Area1D.h"
#include "TESolver1DParams.h"

using namespace std;

class TESolver1DOutput {
private:
    bool printToFile = false;
    bool printXAxes = true;
    bool printT = true;
    bool printHorizontally = false;
    bool printXAxesOnes = false;
    ofstream resultFile;
    bool barePrint = false;
    int NTimeSteps = 100;
    int realNTimeSteps = 50;
    double printNStep = 1;
    bool allowPrintError = true;
public:
    TESolver1DOutput(
            bool printToFile,
            bool printXAxes,
            bool printT,
            bool printHorizontally,
            bool printXAxesOnes,
            const string& resultFilePath,
            bool barePrint,
            int NTimeSteps,
            int maxFrames,
            bool allowPrintError
            ) :
            printToFile(printToFile),
            printXAxes(printXAxes),
            printT(printT),
            printHorizontally(printHorizontally),
            printXAxesOnes(printXAxesOnes),
            barePrint(barePrint && (maxFrames < NTimeSteps)),
            NTimeSteps(NTimeSteps),
            realNTimeSteps(barePrint ? min(maxFrames, NTimeSteps) : NTimeSteps),
            printNStep( (double)NTimeSteps / min(maxFrames, NTimeSteps)),
            allowPrintError(allowPrintError)
            {
        if(printToFile){
            resultFile.open(resultFilePath);
        }
    }

    void printHeader(const TESolver1DParams &params){
        resultFile << params.getCellCount() << "\t" << params.getDx() << endl;
        resultFile << params.getNTimeSteps() << "\t" << realNTimeSteps << "\t" << params.getDt() << endl;
    }

    void print(Area1D &f, int t, double h){
        if(!printToFile) return;

        if(barePrint)
        if(t!=0 && t!=NTimeSteps)
            if((int)(t/printNStep) == (int)((t-1)/printNStep))
                return;

        if(t==0 && printHorizontally && printXAxes && printXAxesOnes){
            for (int i = 0; i < f.size(); i++)
                resultFile << (i + 0.5) * h << "\t";
            resultFile  << endl;
        }

        if(printT)
            resultFile << "t " << t << endl;
        if(printHorizontally) {
            if(printXAxes && !printXAxesOnes) {
                for (int i = 0; i < f.size(); i++)
                    resultFile << (i + 0.5) * h << "\t";
                resultFile << endl;
            }
            for (int i = 0; i < f.size(); i++)
                resultFile << f[i] << "\t";
            resultFile  << endl;
        } else {
            if(printXAxes)
                for (int i = 0; i < f.size(); i++)
                    resultFile << (i + 0.5) * h << "\t" << f[i] << endl;
            else
                for (int i = 0; i < f.size(); i++)
                    resultFile << f[i] << endl;
        }
    }

    void printError(double error){
        if(!allowPrintError) return;
        resultFile << "error " << error << endl;
    }

    void printLine(string& line){
        if(printToFile)
            resultFile << line << endl;
    }

    void finish(){
        if(printToFile)
            resultFile.close();
    }
};

TESolver1DOutput noOutput();
TESolver1DOutput minimal1DOutput(const string& filePath, int NTimeSteps);
TESolver1DOutput normal1DOutput(const string& filePath, int NTimeSteps);
TESolver1DOutput jupyter1DOutput(const string& filePath, int NTimeSteps);

#endif //TRANSPORTEQUATION_TESOLVER1DOUTPUT_H