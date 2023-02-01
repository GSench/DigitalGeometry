//
// Created by grigoriy.senchenok on 21.12.2021.
//

#ifndef TRANSPORTEQUATION_TESOLVER1DOUTPUT_H
#define TRANSPORTEQUATION_TESOLVER1DOUTPUT_H

#include <fstream>
#include <iostream>
#include <vector>
#include <functional>
#include "TESolver1DParams.h"
#include "../Methods/SQuantity.h"
#include "../Methods/Mesh.h"

using namespace std;

static const string TERMINAL = "TERMINAL";

template<typename T>
class TESolver1DOutput {
private:
    bool printToFile = false;
    bool useTerminal = false;
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
    function<string(T)> T2String;

    void print2File(const string& txt){
        if(useTerminal) cout << txt;
        else resultFile << txt;
    }
    void print2File(double d){
        if(useTerminal) cout << to_string(d);
        else resultFile << to_string(d);
    }
    void print2File(int d){
        if(useTerminal) cout << to_string(d);
        else resultFile << to_string(d);
    }
    void printXAxes2File(Mesh<T>& f, const string& separator){
        Mesh<T>* fIter = &f;
        do {
            print2File(fIter->x()); print2File(separator);
            fIter = fIter->next();
        }
        while (!fIter->isBorder());
        print2File(fIter->x()); print2File(separator);
    }
    void printQuantity2File(Mesh<T>& f, const string& separator){
        Mesh<T>* fIter = &f;
        do {
            print2File(T2String(fIter->getQuantity())); print2File(separator);
            fIter = fIter->next();
        }
        while (!fIter->isBorder());
        print2File(T2String(fIter->getQuantity())); print2File(separator);
    }
    void printQuantityWithXAxes2File(Mesh<T>& f, const string& separatorBetween, const string& separatorEnd){
        Mesh<T>* fIter = &f;
        do {
            print2File(fIter->x()); print2File(separatorBetween);
            print2File(T2String(fIter->getQuantity())); print2File(separatorEnd);
            fIter = fIter->next();
        }
        while (!fIter->isBorder());
        print2File(fIter->x()); print2File(separatorBetween);
        print2File(T2String(fIter->getQuantity())); print2File(separatorEnd);
    }
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
            bool allowPrintError,
            function<string(T)> T2String
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
            allowPrintError(allowPrintError),
            T2String(T2String)
            {
        if(printToFile){
            useTerminal = resultFilePath == TERMINAL;
            if(!useTerminal)
                resultFile.open(resultFilePath);
        }
    }

    void printHeader(const TESolver1DParams& params){
        print2File(params.getCellCount());print2File("\t");
        print2File(params.getDx()); print2File("\n");
        print2File(params.getNTimeSteps()); print2File("\t");
        print2File(realNTimeSteps); print2File("\t");
        print2File(params.getDt()); print2File("\n");
    }

    void print(Mesh<T> &f, int t){
        if(!printToFile) return;

        if(barePrint)
            if(t!=0 && t!=NTimeSteps)
                if((int)(t/printNStep) == (int)((t-1)/printNStep))
                    return;

        if(t==0 && printHorizontally && printXAxes && printXAxesOnes){
            printXAxes2File(f, "\t");
            print2File("\n");
        }

        if(printT) {
            print2File("t ");
            print2File(t);
            print2File("\n");
        }
        if(printHorizontally) {
            if(printXAxes && !printXAxesOnes) {
                printXAxes2File(f, "\t");
                print2File("\n");
            }
            printQuantity2File(f, "\t");
            print2File("\n");
        } else {
            if(printXAxes)
                printQuantityWithXAxes2File(f, "\t", "\n");
            else
                printQuantity2File(f, "\n");
        }
    }

    void printError(double error){
        if(!allowPrintError) return;
        print2File("error "); print2File(error); print2File("\n");
    }

    void printLine(string& line){
        if(printToFile) print2File(line+"\n");
    }

    void finish(){
        if(printToFile && !useTerminal)
            resultFile.close();
    }
};

function<string(double)> doublePrinter();

function<string(SQuantity)> rbStatePrinter();

template<typename T>
TESolver1DOutput<T> noOutput(){
    return {false, false, false, false, false, "", false, 0, 0, false, nullptr};
}

template<typename T>
TESolver1DOutput<T> terminal1DOutput(int NTimeSteps, function<string(double)> T2String){
    return {true, true, true, true, false, TERMINAL, false, NTimeSteps, 0, false, T2String};
}

template<typename T>
TESolver1DOutput<T> minimal1DOutput(const string& filePath, int NTimeSteps, int printTimeSteps, function<string(T)> T2String){
        return {true, false, false, true, false, filePath, true, NTimeSteps, printTimeSteps, false, T2String};
    }

template<typename T>
TESolver1DOutput<T> maximal1DOutput(const string& filePath, int NTimeSteps, int printTimeSteps, function<string(T)> T2String){
        return {true, false, false, true, false, filePath, true, NTimeSteps, printTimeSteps, false, T2String};
    }

template<typename T>
TESolver1DOutput<T> normal1DOutput(const string& filePath, int NTimeSteps, int printTimeSteps, function<string(T)> T2String){
    return {true, true, true, true, true, filePath, true, NTimeSteps, printTimeSteps, true, T2String};
    }

template<typename T>
TESolver1DOutput<T> jupyter1DOutput(const string& filePath, int NTimeSteps, int printTimeSteps, function<string(T)> T2String){
        return {true, true, true, false, false, filePath, true, NTimeSteps, printTimeSteps, true, T2String};
}

#endif //TRANSPORTEQUATION_TESOLVER1DOUTPUT_H