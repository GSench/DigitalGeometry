//
// Created by GSench on 14.12.2021.
//

#include "Solver2D.h"
#include "PsyScalar.h"
#include "../Solver1D/THINC1D.h"
#include <functional>
#include <fstream>
#include "../../math/VectorField2D.h"

using namespace std;
/*
void SolveTransportEquation2D(PsyScalar f, function<VectorField2D(int, double)> u, THINC1Dparams p){
    double h = p.area / p.cellCount;
    double timeStep = p.CFL * h / p.u;

    PsyScalar fnext = f;

    ofstream myfile;
    myfile.open(p.resultFilePath);
    myfile << "t=0" << endl;
    f.printToFile(myfile, false);

    for(int n = 0; n < p.stepN; n++){
        for(int xy = X; xy < 2; xy++){
            function<double(double)> PsyPrev = [=](double x)->double {
                return 0;
            };

            for(int ix=0; ix<p.cellCount; ix++){
                for(int iy=0; iy<p.cellCount; iy++){
                    double fi = f.get(ix, iy);
                    double fiPrev = f.getWithOffset(ix, iy, -(xy==X), -(xy==Y));
                    double fiNext = f.getWithOffset(ix, iy, +(xy==X), +(xy==Y));
                    double* cellBounds = (double*) malloc(sizeof(double) * 4);
                    f.getCellBounds(ix, iy, cellBounds);

                    function<double(double)> Psy = p.PsyFunc(fi, fiPrev, fiNext, i, p.beta, h, p.eps);

                    double fiR = Psy(xR - p.u * timeStep / 2); //flow on right cell side is from current cell (upwind)
                    double fiL = PsyPrev(xL - p.u * timeStep / 2); //flow on left cell side is from previous cell (upwind)
                    fnext[i] = fi - p.u / h * (fiR - fiL) * timeStep;

                    PsyPrev = Psy;
                    double xR = (i + 1) * h;
                }

            }
        }
    }
}*/