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

using namespace std;

static const string TERMINAL = "TERMINAL";

template<typename T, typename U>
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
    function<string(U)> U2String;

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
    void printXAxes2File(Quantity<T>& f, const string& separator){
        Quantity<T>* fIter = &f;
        do {
            print2File(fIter->x()); print2File(separator);
            fIter = fIter->next();
        }
        while (!fIter->isBorder());
        print2File(fIter->x()); print2File(separator);
    }
    void printQuantity2File(Quantity<T>& f, const string& separator){
        Quantity<T>* fIter = &f;
        do {
            print2File(T2String(fIter->getQuantity())); print2File(separator);
            fIter = fIter->next();
        }
        while (!fIter->isBorder());
        print2File(T2String(fIter->getQuantity())); print2File(separator);
    }
    void printQuantityWithXAxes2File(Quantity<T>& f, const string& separatorBetween, const string& separatorEnd){
        Quantity<T>* fIter = &f;
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
            function<string(T)> T2String,
            function<string(U)> U2String
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
            T2String(T2String),
            U2String(U2String)
            {
        if(printToFile){
            useTerminal = resultFilePath == TERMINAL;
            if(!useTerminal)
                resultFile.open(resultFilePath);
        }
    }

    void printHeader(const TESolver1DParams<T, U> &params){
        print2File(params.getCellCount());print2File("\t");
        print2File(params.getDx()); print2File("\n");
        print2File(params.getNTimeSteps()); print2File("\t");
        print2File(realNTimeSteps); print2File("\t");
        print2File(params.getDt()); print2File("\n");
    }

    void print(Quantity<T> &f, int t){
        if(!printToFile) return;

        if(barePrint)
            if(t!=0 && t!=NTimeSteps)
                if((int)(t/printNStep) == (int)((t-1)/printNStep))
                    return;

        if(t==0 && printHorizontally && printXAxes && printXAxesOnes){
            printXAxes2File(f, "\t");
            print2File("\n");
        }

        if(printT)
            print2File("t "); print2File(t); print2File("\n");
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

function<string(double)> printVolumeFraction();

TESolver1DOutput<double,double> noOutput();
template<typename T>
TESolver1DOutput<T,double> terminal1DOutput(int NTimeSteps, function<string(T)> T2String);
template<typename T>
TESolver1DOutput<T,double> minimal1DOutput(const string& filePath, int NTimeSteps, function<string(T)> T2String);
template<typename T>
TESolver1DOutput<T,double> maximal1DOutput(const string& filePath, int NTimeSteps, function<string(T)> T2String);
template<typename T>
TESolver1DOutput<T,double> normal1DOutput(const string& filePath, int NTimeSteps, function<string(T)> T2String);
template<typename T>
TESolver1DOutput<T,double> jupyter1DOutput(const string& filePath, int NTimeSteps, function<string(T)> T2String);

#endif //TRANSPORTEQUATION_TESOLVER1DOUTPUT_H