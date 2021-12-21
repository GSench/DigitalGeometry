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
#include "StandardSolver.h"

using namespace std;

const string OUTPUT_PATH = R"(C:\Programing\Projects\DigitalGeometry\Programs\Output\)";

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

bool compare1DSolutions(const vector<double>& f1, const vector<double>& f2, int cellCount, double acceptDiffer){
    bool FAIL = false;
    for(int i=0; i<cellCount; i++){
        double diff = abs(f1[i]-f2[i]);
        if(diff > acceptDiffer){
            cout <<
                 "ERROR at " << i << " cell: " <<
                 "f1 = " << f1[i] << " , f2 = " << f2[i] <<
                 " difference = " << diff << endl;
            FAIL = true;
        }
    }
    return !FAIL;
}

bool test1DSolutionWithFile(const vector<double>& f,
                            const string& debugFilePath,
                            double cellCount,
                            double acceptDiffer) {
    ifstream debugFile(debugFilePath);
    double xiDebug, fiDebug;
    string s;
    double v, error = 0;
    vector<double> fDebug(cellCount, 0.0);
    cout << "READING FILE: " << debugFilePath << endl;
    while(true){
        debugFile >> s >> v;
        if(s=="error"){
            //cout << "error = "<< v << endl;
            error = v;
            break;
        } else if(s=="t") {
            //cout << "t = " << v << endl;
            for(int i=0; i<cellCount; i++){
                debugFile >> xiDebug >> fiDebug;
                fDebug[i] = fiDebug;
            }
        }
    }


    return compare1DSolutions(f, fDebug, cellCount, acceptDiffer);
}

void test1DSolverWithFile(){
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
    int i = 8;
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
    bool testResult = test1DSolutionWithFile(f, debugFilePath, params.cellCount, 1e-6);

    cout << endl <<
         "------------------" << endl <<
         "Psy function: " << params.PsyFuncName << endl <<
         "cellCount: " << params.cellCount << " stepN: " << params.stepN << endl <<
         "CFL: " << params.CFL << " Area size: " << params.area << endl <<
         "beta: " << params.beta << " eps: " << params.eps << " u: " << params.u << endl <<
         "------------------" << endl <<
         (testResult ? "TEST SUCCEEDED" : "TEST FAILED") << endl;
}

void test1DSolverStandard(){
    // Debug params
    THINC1DparamsDebug paramsDebug;

    // Scalar params
    paramsDebug.area = 1;
    paramsDebug.u = 0.1;
    paramsDebug.eps = 1e-4;
    paramsDebug.beta = 3.5;

    // Test specific params
    paramsDebug.PsyFunc = [=](const vector<double>& f, int i, double beta, double h, double eps)->function<double(double)> {
        return PsyTHINCandMUSCLDebug(f, i, beta, h, eps);
    };

    paramsDebug.CFL = 0.3;

    int i = 8;
    int N = paramsDebug.CFL * 10.0 * pow(2, i);
    paramsDebug.cellCount = N;

    int T = (double) N / paramsDebug.CFL;
    int j = 6;
    int time = T * j;
    paramsDebug.stepN = time;

    THINC1Dparams params;
    params.area = 1;
    params.u = 0.1;
    params.eps = 1e-4;
    params.beta = 3.5;
    params.PsyFunc = [=](double fi, double fiPrev, double fiNext, int i, double b, double h, double e)->function<double(double)> {
        return PsyTHINCandMUSCL(fi, fiPrev, fiNext, i, b, h, e);
    };
    params.PsyFuncName = "Psy THINC + MUSCL";
    params.resultFilePath = "";
    params.CFL = 0.3;
    params.cellCount = N;
    params.stepN = time;


    // f init
    double L = N / 2;
    double R = N - 1;
    vector<double> f(N);
    initF(f, L, R);
    vector<double> fexact = f;

    vector<double> fStd = f;
    vector<double> fExStd = fexact;

    cout << "Computing with current solver" << endl;
    THINC1D(params, f, fexact);
    cout << "Computing with standard solver" << endl;
    THINC1DDebug(paramsDebug, fStd, fExStd);
    /*for(int i=0; i<fStd.size(); i++)
        cout << i << "\t" << fStd[i] << endl;*/
    cout << "Comparing solutions" << endl;
    bool testResult = compare1DSolutions(f, fStd, params.cellCount, 0.0);

    cout << endl <<
         "------------------" << endl <<
         "Psy function: " << params.PsyFuncName << endl <<
         "cellCount: " << params.cellCount << " stepN: " << params.stepN << endl <<
         "CFL: " << params.CFL << " Area size: " << params.area << endl <<
         "beta: " << params.beta << " eps: " << params.eps << " u: " << params.u << endl <<
         "------------------" << endl <<
         (testResult ? "TEST SUCCEEDED" : "TEST FAILED") << endl;
}