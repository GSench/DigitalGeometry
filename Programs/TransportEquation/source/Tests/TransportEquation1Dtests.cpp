//
// Created by GSench on 14.12.2021.
//

#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <functional>

#include "TransportEquation1Dtests.h"
#include "../TransportEquationSolver/InterpolationFunctions.h"
#include "../TransportEquationSolver/Solver1D/THINC1D.h"

using namespace std;

const string OUTPUT_PATH = R"(C:\Programing\C++\TransportEquation\)";

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
                params.resultFilePath = OUTPUT_PATH+"CalculationResults/" + titles[psy] + "/N" + std::to_string(N) + "_T" + std::to_string(j + 1) + ".txt";
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