//
// Created by grigoriy.senchenok on 21.02.2022.
//

#include <string>
#include "DigitalGeometryTests2D.h"
#include "../configs.h"

using namespace std;

void StripSinMoveTest(){
    const string TEST_TITLE = "StripSinMoveTest";
    const string testDir = initTest(TEST_TITLE, CALCULATION_DG1D_OUTPUT_PATH);

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

    SolveDG1D(f, params, vc, out);

}