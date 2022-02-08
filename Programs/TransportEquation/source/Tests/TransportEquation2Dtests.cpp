//
// Created by grigoriy.senchenok on 08.02.2022.
//

#include "TransportEquation2Dtests.h"
#include "../TransportEquationSolver/Solver2D/Solver2DInstances.h"
#include "../TransportEquationSolver/InterpolationFunctions.h"
#include "../TransportEquationSolver/Solver2D/Solver2DOutput.h"
#include "../TransportEquationSolver/Solver2D/VectorField2D.h"
#include "../TransportEquationSolver/Solver2D/Solver2D.h"

const string OUTPUT_PATH = R"(../../Output/)";

void Solve2DRectMovementTest(){
    Solver2DParams params = get2DParamsFor(
            0.3,
            0.15,
            1.0,
            1.0,
            128,
            200,
            [=](F1D f1D, C1D c1D) -> function<double(double)> {
                return PsyTHINCandGodunov(f1D, c1D, 3.5, 1e-4);
            },
            "Psy THINC + Godunov"
    );

    Solver2DOutput out = minimal2DOutput(OUTPUT_PATH + "CalculationResults/Solve2DRectMovementTest.txt",
                                            params.NTimeSteps);

    Area2D f(params.cellCountX, params.cellCountY);
    f.drawRect(1, 10, 10, 10, 10);

    VectorField2D u = getStaticVF2D({0.1, 0.1}, params.cellCountX+1, params.cellCountY+1);

    SolveTransportEquation2D(f, u, params, out);

}