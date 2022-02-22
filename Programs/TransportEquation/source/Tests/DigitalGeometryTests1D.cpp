//
// Created by grigoriy.senchenok on 21.02.2022.
//

#include "../TransportEquationSolver/Solver1D/Solver1DInstances.h"
#include "../TransportEquationSolver/InterpolationFunctions.h"
#include "../configs.h"
#include "Tests.h"
#include "../TransportEquationSolver/Solver1D/Solver1DOutput.h"
#include "../Utils/FileUtils.h"
#include "../TransportEquationSolver/Solver1D/VectorField1D.h"
#include "../DGProblem/DGSolver1D/DGSolver1D.h"
#include <cmath>


void StripSinMoveTest(){
    const string TEST_TITLE = "StripSinMoveTest";
    const string testDir = initTest(TEST_TITLE, CALCULATION_1D_OUTPUT_PATH);

    Solver1DParams params = getParamsFor(
            0.3,
            0.1,
            1.0,
            64,
            200,
            [=](F1D f1D, C1D c1D) -> function<double(double)> {
                return PsyTHINCandGodunov(f1D, c1D, 3.5, 1e-4);
            },
            "Psy THINC + Godunov"
    );
    EESolver1DParams uParams = {
            params.dt,
            params.areaLength,
            params.cellCount,
            params.NTimeSteps,
            params.dx
    };

    Solver1DOutput out = minimal1DOutput(
            downDir(
                    testDir,
                    "area_" + to_string(params.cellCount) + "_t_" + to_string(params.NTimeSteps) + ".txt"),
            params.NTimeSteps);
    out.printHeader(params);

    Area1D f(params.cellCount, false);
    f.drawStructCount(1, 24, 16);

    function<double(double)> vc = [=](double t) -> double {
        return cos(t) * 0.1;
    };
    VectorField1D u(params.cellCount+1);

    SolveDG1D(f, params, u,  uParams, vc, out);

}
