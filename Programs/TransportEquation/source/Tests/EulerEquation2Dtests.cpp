//
// Created by grigoriy.senchenok on 21.02.2022.
//

#include "EulerEquation2Dtests.h"

#include "../configs.h"
#include "Tests.h"
#include "../EulerEquationProblem/EESolver2D/EESolver2DParams.h"
#include "../math/Vector2D.h"
#include "../EulerEquationProblem/EESolver2D/EESolver2DOutput.h"
#include "../EulerEquationProblem/EESolver2D/EESolver2D.h"
#include "../math/VectorMeshTools.h"
#include "../Utils/FileUtils.h"

void ParabolicCenterTest(){
    const string TEST_TITLE = "ParabolicCenterTest";
    const string testDir = initTest(TEST_TITLE, CALCULATION_EE2D_OUTPUT_PATH);

    EESolver2DParams params(100, 1.0);
    vector<Vector2D> mesh = {Vector2D()};
    function<Vector2D(double)> vc = [=](double t)->Vector2D{
        return {0.1, 1.-2*t};
    };
    vector<Vector2D> vcMesh = mesh1D(vc, 0, params.NTimeSteps+1, params.dt);
    function<double(double)> omega = [=](double t)->double {
        return 0;
    };
    EESolver2DOutput out = minimal2DOutputEE(
            downDir(testDir,"t_" + to_string(params.NTimeSteps) + ".txt"),
            params.NTimeSteps);

    SolveEE2D(mesh, vcMesh, omega, params, out);

    cout << "Final positions:" << endl;
    for(int i=0; i<mesh.size(); i++)
        cout << i << ": x = " << mesh[i].x << "; y = " << mesh[i].y << endl;
}