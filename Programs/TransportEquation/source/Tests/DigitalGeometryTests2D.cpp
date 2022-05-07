//
// Created by grigoriy.senchenok on 21.02.2022.
//

#include <string>
#include <iostream>
#include "../configs.h"
#include "Tests.h"
#include "../DGProblem/DGSolver2D/DGSolver2DParams.h"
#include "../TransportEquationSolver/Tools/InterpolationFunctions.h"
#include "../DGProblem/DGSolver2D/DGSolver2DOutput.h"
#include "../Utils/FileUtils.h"
#include "../math/VectorMeshTools.h"
#include "../DGProblem/DGSolver2D/DGSolver2D.h"

using namespace std;

void PlusRotateTest(){
    const string TEST_TITLE = "PlusRotateTest";
    const string testDir = initTest(TEST_TITLE, CALCULATION_DG2D_OUTPUT_PATH);

    double w = 2.0;
    double h = 2.0;
    double t = 1.0;
    int N = 128;
    int T = 128;
    DGSolver2DParams params (
            w/N,
            N,
            N,
            t/T,
            T,
            [=](F1D f1D, C1D c1D) -> function<double(double)> {
                return PsyTHINCandGodunov(f1D, c1D, 3.5, 1e-4);
            }
    );
    cout << "Psy THINC + Godunov" << endl;

    DGSolver2DOutput out = minimal2DOutputDG(
            downDir(
                    testDir,
                    "TE_area_" + to_string(N) + "_t_" + to_string(T) + ".txt"),
            downDir(
                    testDir,
                    "EE_t_" + to_string(T) + ".txt"),
            T);
    out.printHeader(params);

    Area2D f(N, N);
    f.drawRect(1.0, N/2-N/4, N/2-N/4-10, 10, 30);
    f.drawRect(1.0, N/2-N/4-10, N/2-N/4, 30, 10);

    vector<Vector2D> mesh = {Vector2D(w/N*(N/2-N/4), h/N*(N/2-N/4))};
    function<Vector2D(double)> vc = [=](double t)->Vector2D{
        return {1, 4-8*t};
    };
    vector<Vector2D> vcMesh = mesh1D(vc, 0, T+1, params.getParamsForEE2D().getDt());
    function<double(double)> omega = [=](double t)->double {
        return 1.0;
    };
    vector<double> omegaMesh = mesh1D(omega, 0, T+1, params.getParamsForEE2D().getDt());

    SolveDG2D(f, mesh, vcMesh, omegaMesh, params, out);

    out.finish();

}