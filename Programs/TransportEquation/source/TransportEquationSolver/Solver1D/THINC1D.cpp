#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <functional>

#include "THINC1D.h"
#include "../InterpolationFunctions.h"

using namespace std;

void initF(vector<double> &f, int L, int R) {
    for (int i = 0; i < L; i++)
        f[i] = 0;
    f[L] = 1;
    for (int i = L + 1; i < R; i++)
        f[i] = 1;
    f[R] = 1;
    for (int i = R + 1; i < f.size(); i++)
        f[i] = 0;
}

double THINC1D(const THINC1Dparams& p, vector<double> &f, const vector<double>& fexact) {
    double h = p.area / p.cellCount;
    double timeStep = p.CFL * h / p.u;

    vector<double> fnext = f;

    ofstream myfile;
    myfile.open(p.resultFilePath);
    myfile << "t=0" << endl;
    for (int i = 0; i < p.cellCount; i++) {
        myfile << (i+0.5)*h << "\t" << f[i] << endl;
    }

    for (int n = 0; n < p.stepN; n++) {

        //first previous Psy is from last cell (cycled space)
        function<double(double)> PsyPrevVirt = p.PsyFunc(f, p.cellCount - 1, p.beta, h, p.eps);
        function<double(double)> PsyPrev = [=](double x)->double {
            return PsyPrevVirt(x+p.cellCount*h);
        };

        for (int i = 0; i < p.cellCount; i++) {
            int iPrev = i != 0 ? i - 1 : p.cellCount - 1;
            int iNext = i != p.cellCount - 1 ? i + 1 : 0;

            double fi = f[i];
            double fiPrev = f[iPrev];
            double fiNext = f[iNext];
            double xL = i * h;
            double xR = (i + 1) * h;

            function<double(double)> Psy = p.PsyFunc(f, i, p.beta, h, p.eps);

            double fiR = Psy(xR - p.u * timeStep / 2); //flow on right cell side is from current cell (upwind)
            double fiL = PsyPrev(xL - p.u * timeStep / 2); //flow on left cell side is from previous cell (upwind)
            fnext[i] = fi - p.u / h * (fiR - fiL) * timeStep;
            
            PsyPrev = Psy;
        }
        myfile << "t="<< n+1 << endl;
        for (int i = 0; i < p.cellCount; i++) {
            f[i] = fnext[i];
            myfile << (i + 0.5) * h << "\t" << f[i] << endl;
        }
    }

    double error = 0;
    for (int i = 0; i < p.cellCount; i++) {
        error += pow(f[i]*h - fexact[i] * h, 2);
    }
    error = sqrt(error);

    myfile << "error=" << error;

    myfile.close();
    return error;
}

