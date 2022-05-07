//
// Created by grigoriy.senchenok on 07.05.2022.
//

#ifndef TRANSPORTEQUATION_DGSOLVER2DOUTPUT_H
#define TRANSPORTEQUATION_DGSOLVER2DOUTPUT_H


#include "../../TransportEquationSolver/Solver2D/TESolver2DOutput.h"
#include "../../EulerEquationProblem/EESolver2D/EESolver2DOutput.h"
#include "DGSolver2DParams.h"

class DGSolver2DOutput {
private:
    TESolver2DOutput teOutput;
    EESolver2DOutput eeOutput;

public:
    DGSolver2DOutput(
            bool printToFile,
            bool printT,
            const string& resultTEFilePath,
            const string& resultEEFilePath,
            bool barePrint,
            int NTimeSteps,
            int maxFrames
    ) :
            teOutput(printToFile, printT, resultTEFilePath, barePrint, NTimeSteps, maxFrames),
            eeOutput(printToFile, printT, resultEEFilePath, barePrint, NTimeSteps, maxFrames)
    {}

    void printHeader(DGSolver2DParams params){
        teOutput.printHeader(params.getParamsForTE2D());
        eeOutput.printHeader(params.getParamsForEE2D());
    }

    void print(Area2D& area, const vector<Vector2D>& points, int it){
        teOutput.print(area, it);
        eeOutput.print(points, it);
    }
};

DGSolver2DOutput no2DOutputDG();
DGSolver2DOutput minimal2DOutputDG(const string& filePathTE, const string& filePathEE, int NTimeSteps);


#endif //TRANSPORTEQUATION_DGSOLVER2DOUTPUT_H
