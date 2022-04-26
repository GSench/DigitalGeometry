//
// Created by grigoriy.senchenok on 21.02.2022.
//

#include "../TransportEquationSolver/Instances/TESolver1DInstances.h"
#include "../TransportEquationSolver/Tools/InterpolationFunctions.h"
#include "../configs.h"
#include "Tests.h"
#include "../TransportEquationSolver/Solver1D/TESolver1DOutput.h"
#include "../Utils/FileUtils.h"
#include "../TransportEquationSolver/Instances/VectorField1D.h"
#include "../DGProblem/DGSolver1D/DGSolver1D.h"
#include <cmath>


void StripSinMoveTest(){
    const string TEST_TITLE = "StripSinMoveTest";
    const string testDir = initTest(TEST_TITLE, CALCULATION_1D_OUTPUT_PATH);

    TESolver1DParams params (
            0.3,
            0.1,
            1.0,
            64,
            200,
            [=](F1D f1D, C1D c1D) -> function<double(double)> {
                return PsyTHINCandGodunov(f1D, c1D, 3.5, 1e-4);
            }
    );
    cout << "Psy THINC + Godunov" << endl;
    EESolver1DParams uParams = {
            params.getDt(),
            params.getNTimeSteps(),
            params.getDx(),
            params.getCellCount()
    };

    TESolver1DOutput out = minimal1DOutput(
            downDir(
                    testDir,
                    "area_" + to_string(params.getCellCount()) + "_t_" + to_string(params.getNTimeSteps()) + ".txt"),
            params.getNTimeSteps());
    out.printHeader(params);

    Area1D f(params.getCellCount(), false);
    f.drawStructCount(1, 24, 16);

    function<double(double)> vc = [=](double t) -> double {
        return cos(t) * 0.1;
    };
    VectorField1D u(params.getCellCount()+1);

    SolveDG1D(f, params, u,  uParams, vc, out);

}
