//
// Created by GSench on 14.12.2021.
//

#include "Solver2D.h"
#include "PsyScalar.h"
#include "../Solver1D/Solver1D.h"
#include <functional>
#include <fstream>
#include "../../math/VectorField2D.h"

using namespace std;
/*
void SolveTransportEquation2D(PsyScalar scalarFunction, function<VectorField2D(int, double)> uMax, Area1D p){
    double h = p.areaLength / p.cellCount;
    double timeStep = p.CFL * h / p.uMax;

    PsyScalar fnext = scalarFunction;

    ofstream myfile;
    myfile.open(p.resultFilePath);
    myfile << "t=0" << endl;
    scalarFunction.printToFile(myfile, false);

    for(int n = 0; n < p.NTimeSteps; n++){
        for(int xy = X; xy < 2; xy++){
            function<double(double)> PsyPrev = [=](double x)->double {
                return 0;
            };

            for(int ix=0; ix<p.cellCount; ix++){
                for(int iy=0; iy<p.cellCount; iy++){
                    double fi = scalarFunction.get(ix, iy);
                    double fiPrev = scalarFunction.getWithOffset(ix, iy, -(xy==X), -(xy==Y));
                    double fiNext = scalarFunction.getWithOffset(ix, iy, +(xy==X), +(xy==Y));
                    double* cellBounds = (double*) malloc(sizeof(double) * 4);
                    scalarFunction.getCellBounds(ix, iy, cellBounds);

                    function<double(double)> Psy = p.FlowInterpolationFunction(fi, fiPrev, fiNext, i, p.beta, h, p.eps);

                    double fiR = Psy(xR - p.uMax * timeStep / 2); //flow on right cell side is from current cell (upwind)
                    double fiL = PsyPrev(xL - p.uMax * timeStep / 2); //flow on left cell side is from previous cell (upwind)
                    fnext[i] = fi - p.uMax / h * (fiR - fiL) * timeStep;

                    PsyPrev = Psy;
                    double xR = (i + 1) * h;
                }

            }
        }
    }
}*/