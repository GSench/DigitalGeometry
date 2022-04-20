//
// Created by grigoriy.senchenok on 08.02.2022.
//

#include "TransportEquation2Dtests.h"
#include "../TransportEquationSolver/Solver2D/TESolver2DParams.h"
#include "../TransportEquationSolver/InterpolationFunctions.h"
#include "../TransportEquationSolver/Solver2D/Solver2DOutput.h"
#include "../TransportEquationSolver/Solver2D/VectorField2D.h"
#include "../TransportEquationSolver/Solver2D/Solver2D.h"
#include "../configs.h"
#include "Tests.h"
#include "../Utils/FileUtils.h"

void Solve2DRectMovementTest() {
    const string TEST_TITLE = "Solve2DRectMovementTest";
    const string testDir = initTest(TEST_TITLE, CALCULATION_2D_OUTPUT_PATH);

    TESolver2DParams params(
            0.3,
            0.15,
            1.0,
            1.0,
            128,
            400,
            [=](F1D f1D, C1D c1D) -> function<double(double)> {
                return PsyTHINCandGodunov(f1D, c1D, 3.5, 1e-4);
            }
    );
    cout << "Using Psy THINC + Godunov" << endl;

    Solver2DOutput out = minimal2DOutput(downDir(
                                                 testDir,
                                                 "area_"
                                                 +to_string(params.getCellCountX())+"x"+to_string(params.getCellCountY())
                                                 +"_t_" + to_string(params.getNTimeSteps())+".txt"),
                                         params.getNTimeSteps());
    out.printHeader(params);

    Area2D f(params.getCellCountX(), params.getCellCountY());
    f.drawRect(1, 10, 10, 30, 30);

    VectorField2D u = getStaticVF2D({0.1, 0.1}, params.getCellCountX()+1, params.getCellCountY()+1);

    SolveTransportEquation2D(f, u, params, out);

}

void Solve2DWhiteBearMovementTest(){
    const string TEST_TITLE = "Solve2DWhiteBearMovementTest";
    const string testDir = initTest(TEST_TITLE, CALCULATION_2D_OUTPUT_PATH);

    TESolver2DParams params (
            0.3,
            0.15,
            1.0,
            1.0,
            128,
            400,
            [=](F1D f1D, C1D c1D) -> function<double(double)> {
                return PsyTHINCandGodunov(f1D, c1D, 3.5, 1e-4);
            }
    );
    cout << "Using Psy THINC + Godunov" << endl;

    Solver2DOutput out = minimal2DOutput(downDir(
                                                 testDir,
                                                 "area_"
                                                 +to_string(params.getCellCountX())+"x"+to_string(params.getCellCountY())
                                                 +"_t_" + to_string(params.getNTimeSteps())+".txt"),
                                         params.getNTimeSteps());
    out.printHeader(params);

    Area2D f(params.getCellCountX(), params.getCellCountY());
    f.drawRect(1, 10, 10, 10, 20);
    f.drawRect(1, 20, 20, 10, 20);
    f.drawRect(1, 30, 10, 10, 20);

    VectorField2D u = getStaticVF2D({0.1, 0.1}, params.getCellCountX()+1, params.getCellCountY()+1);

    SolveTransportEquation2D(f, u, params, out);
}