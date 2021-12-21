//
// Created by grigoriy.senchenok on 21.12.2021.
//

#ifndef TRANSPORTEQUATION_SOLVER1DOUTPUT_H
#define TRANSPORTEQUATION_SOLVER1DOUTPUT_H

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class Solver1DOutput {
private:
    bool printToFile = false;
    bool printXAxes = true;
    bool printT = true;
    ofstream resultFile;
public:
    Solver1DOutput(
            bool printToFile,
            bool printXAxes,
            bool printT,
            const string& resultFilePath) :
            printToFile(printToFile),
            printXAxes(printXAxes),
            printT(printT) {
        if(printToFile){
            resultFile.open(resultFilePath);
        }
    }

    void print(const vector<double>& f, int t, double h){
        if(!printToFile) return;
        if(printT)
            resultFile << "t " << t << endl;
        if(printXAxes)
            for (int i = 0; i < f.size(); i++)
                resultFile << (i + 0.5) * h << "\t" << f[i] << endl;
        else
            for (double fi : f) resultFile << fi << endl;
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

Solver1DOutput noOutput();

#endif //TRANSPORTEQUATION_SOLVER1DOUTPUT_H
