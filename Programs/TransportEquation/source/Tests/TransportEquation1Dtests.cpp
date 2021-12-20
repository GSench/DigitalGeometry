//
// Created by GSench on 14.12.2021.
//

#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <iterator>

#include "TransportEquation1Dtests.h"
#include "../TransportEquationSolver/InterpolationFunctions.h"
#include "../TransportEquationSolver/Solver1D/THINC1D.h"

using namespace std;

const string OUTPUT_PATH = R"(C:\Programing\Projects\DigitalGeometry\Programs\Output\)";

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
            [&](double fi, double fiPrev, double fiNext, int i, double b, double h, double e)->function<double(double)> {
                return PsyTHINCandGodunov(fi, fiPrev, fiNext, i, b, h, e);
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
    params.PsyFunc = [&](double fi, double fiPrev, double fiNext, int i, double b, double h, double e)->function<double(double)> {
        return PsyTHINCandMUSCL(fi, fiPrev, fiNext, i, b, h, e);
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

    vector< function<function<double(double)>(double, double, double, int, double, double, double)> > PsyFunctions(4);
    PsyFunctions[0] = [=](double fi, double fiPrev, double fiNext, int i, double b, double h, double e)->function<double(double)> {
        return PsyGodunov(fi);
    };
    PsyFunctions[1] = [=](double fi, double fiPrev, double fiNext, int i, double b, double h, double e)->function<double(double)> {
        return PsyMUSCL(fi, fiPrev, fiNext, i, h);
    };
    PsyFunctions[2] = [=](double fi, double fiPrev, double fiNext, int i, double b, double h, double e)->function<double(double)> {
        return PsyTHINCandGodunov(fi, fiPrev, fiNext, i, b, h, e);
    };
    PsyFunctions[3] = [=](double fi, double fiPrev, double fiNext, int i, double b, double h, double e)->function<double(double)> {
        return PsyTHINCandMUSCL(fi, fiPrev, fiNext, i, b, h, e);
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

void test1DSolution(const vector<double>& f,
                    const string& debugFilePath,
                    const THINC1Dparams& params,
                    double acceptDiffer) {
    ifstream debugFile(debugFilePath);
    double fiDebug;
    istream_iterator<double> start(debugFile), end;
    vector<double> fDebug(start, end);
    bool FAIL = false;
    for(int i=0; i<params.cellCount; i++){
        if(abs(f[i]-fDebug[i]) > acceptDiffer){
            cout <<
            "ERROR at " << i << " cell: " <<
            "fNew = " << f[i] << " , fOld = " << fDebug[i] <<
            " difference = " << abs(f[i]-fDebug[i]) << endl;
            FAIL = true;
        }
    }
    cout << endl <<
    "------------------" << endl <<
    "Psy function: " << params.PsyFuncName << endl <<
    "cellCount: " << params.cellCount << " stepN: " << params.stepN << endl <<
    "CFL: " << params.CFL << " Area size: " << params.area << endl <<
    "beta: " << params.beta << " eps: " << params.eps << " u: " << params.u << endl <<
    "------------------" << endl <<
    (FAIL ? "TEST FAILED" : "TEST SUCCEEDED") << endl;
}

void test1DSolver(){
    // Debug params
    THINC1Dparams params;

    // Scalar params
    params.area = 1;
    params.u = 0.1;
    params.eps = 1e-4;
    params.beta = 3.5;

    // Test specific params
    params.PsyFunc = [=](double fi, double fiPrev, double fiNext, int i, double b, double h, double e)->function<double(double)> {
        return PsyTHINCandMUSCL(fi, fiPrev, fiNext, i, b, h, e);
    };
    params.PsyFuncName = "Psy THINC + MUSCL";
    params.CFL = 0.3;
    int i = 9;
    int N = params.CFL * 10.0 * pow(2, i);
    params.cellCount = N;
    int T = (double) N / params.CFL;
    int j = 6;
    params.stepN = T * j;

    // f init
    double L = N / 2;
    double R = N - 1;
    vector<double> f(N);
    initF(f, L, R);
    vector<double> fexact = f;

    THINC1D(params, f, fexact);

    string debugFilePath =
            "C:\\Programing\\Projects\\DigitalGeometry\\Programs\\Output\\StandardResults\\THINC_MUSCL\\N768_T6.txt";
    test1DSolution(f, debugFilePath, params, 0.0);
}