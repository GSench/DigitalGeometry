#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <functional>

#include "THINC1D.h"
#include "InterpolationFunctions.h"

using namespace std;

const string OUTPUT_PATH = R"(C:\Programing\C++\TransportEquation\)";

struct THINC1Dparams {
    int cellCount = 20;
    double area = 1;
    int stepN = 100;
    double CFL = 0.3;
    double u = 0.1;
    double eps = 1e-4;
    double beta = 3.5;
    std::string resultFilename = "THINC1DOutput.txt";
    function<function<double(double)>(vector<double>, int, double, double, double)> PsyFunc =
        [&](const vector<double>& f, int i, double b, double h, double e)->function<double(double)> {
        return PsyTHINCandMUSCL(f, i, b, h, e);
    };
};

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
    myfile.open(OUTPUT_PATH+p.resultFilename);
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

void oldTestCompare() {
    THINC1Dparams params;
    params.cellCount = 20;
    int hsL = params.cellCount / 2;
    params.area = 1;
    params.stepN = 100;
    params.CFL = 0.3;
    params.u = 0.1;
    params.eps = 1e-4;
    params.beta = 3.5;
    vector<double> f(params.cellCount);
    initF(f, hsL, params.cellCount-1);
    f[hsL - 1] = 0.5;
    f[0] = 0.5;
    vector<double> fexact = f;
    params.PsyFunc =
        [&](const vector<double>& f, int i, double b, double h, double e)->function<double(double)> {
            return PsyTHINCandGodunov(f, i, b, h, e);
    };
    THINC1D(params, f, fexact);
}

void debugDifference(){
    THINC1Dparams params;
    int N = 12;
    params.cellCount = N;
    double L = N / 2;
    double R = N - 1;
    vector<double> f(N);
    initF(f, L, R);
    vector<double> fexact = f;
    int T = (double)N / params.CFL;
    params.stepN = T*2;
    params.PsyFunc = [&](const vector<double>& f, int i, double b, double h, double e)->function<double(double)> {
        return PsyTHINCandMUSCL(f, i, b, h, e);
    };
    THINC1D(params, f, fexact);
}

void THINC1Dtests() {

    int iNmax = 9;
    int iNmin = 3;
    int jTmax = 6;

    THINC1Dparams params;

    ofstream myfi;
    myfi.open(OUTPUT_PATH+"CalculationResults/error.txt");
    myfi << endl;

    vector< function<function<double(double)>(vector<double>, int, double, double, double)> > PsyFunctions(4);
    PsyFunctions[0] = [&](const vector<double>& f, int i, double b, double h, double e)->function<double(double)> {
        return PsyGodunov(f, i, b, h, e);
    };
    PsyFunctions[1] = [&](const vector<double>& f, int i, double b, double h, double e)->function<double(double)> {
        return PsyMUSCL(f, i, b, h, e);
    };
    PsyFunctions[2] = [&](const vector<double>& f, int i, double b, double h, double e)->function<double(double)> {
        return PsyTHINCandGodunov(f, i, b, h, e);
    };
    PsyFunctions[3] = [&](const vector<double>& f, int i, double b, double h, double e)->function<double(double)> {
        return PsyTHINCandMUSCL(f, i, b, h, e);
    };

    vector<string> titles{ "Godunov", "MUSCL", "THINC_Godunov", "THINC_MUSCL" };

    for (int psy = 0; psy < PsyFunctions.size(); psy++) {
        cout << titles[psy] << " scheme" << endl;
        myfi << titles[psy] << " scheme" << endl;
        params.PsyFunc = PsyFunctions[psy];

        cout << " \t";
        for (int j = 0; j < jTmax; j++)
            cout << "T" << (j + 1) << "\t";
        cout << endl;
        myfi << " \t";
        for (int j = 0; j < jTmax; j++)
            myfi << "T" << (j + 1) << "\t";
        myfi << endl;

        for (int i = iNmin; i < iNmax; i++) {
            int N = params.CFL * 10.0 * pow(2, i); //params.CFL*10 чтобы N был кратен CFL
            params.cellCount = N;
            double L = N / 2;
            double R = N - 1;
            vector<double> f(N);
            initF(f, L, R);
            vector<double> fexact = f;

            int T = (double)N / params.CFL;
            params.stepN = T;

            cout << "N" << N << "\t";
            myfi << "N" << N << "\t";
            for (int j = 0; j < jTmax; j++) {
                params.resultFilename = "CalculationResults/" + titles[psy] + "/N" + std::to_string(N) + "_T" + std::to_string(j + 1) + ".txt";
                double error = THINC1D(params, f, fexact);
                printf("%.4f\t", error);
                myfi << error << "\t";
            }
            cout << endl;
            myfi << endl;
        }
        cout << endl;
        myfi << endl;
    }
    myfi.close();
    
}
