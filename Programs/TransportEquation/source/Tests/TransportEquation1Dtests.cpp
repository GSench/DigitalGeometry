//
// Created by GSench on 14.12.2021.
//

#include <math.h>
#include <iostream>
#include <vector>
#include <functional>
#include <iterator>

#include "TransportEquation1Dtests.h"
#include "../TransportEquationSolver/InterpolationFunctions.h"
#include "../TransportEquationSolver/Solver1D/Solver1D.h"
#include "StandardSolver.h"
#include "../TransportEquationSolver/Solver1D/Solver1DOutput.h"
#include "../TransportEquationSolver/Solver1D/Area1D.h"
#include "../TransportEquationSolver/Solver1D/VectorField1D.h"

using namespace std;

const string OUTPUT_PATH = R"(C:\Programing\Projects\DigitalGeometry\Programs\Output\)";
/*
void THINC1Dtests() {

    int iNmax = 9;
    int iNmin = 3;
    int jTmax = 6;

    Area1D params;

    ofstream myfi;
    myfi.open(OUTPUT_PATH+"CalculationResults/error.txt");
    myfi << endl;

    double b = 3.5;
    double e = 1e-4;
    vector< function<function<double(double)>(double, double, double, int, double)> > PsyFunctions(4);
    PsyFunctions[0] = [=](double fi, double fiPrev, double fiNext, int i, double h)->function<double(double)> {
        return PsyGodunov(fi);
    };
    PsyFunctions[1] = [=](double fi, double fiPrev, double fiNext, int i, double h)->function<double(double)> {
        return PsyMUSCL(fi, fiPrev, fiNext, i, h);
    };
    PsyFunctions[2] = [=](double fi, double fiPrev, double fiNext, int i, double h)->function<double(double)> {
        return PsyTHINCandGodunov(fi, fiPrev, fiNext, i, b, h, e);
    };
    PsyFunctions[3] = [=](double fi, double fiPrev, double fiNext, int i, double h)->function<double(double)> {
        return PsyTHINCandMUSCL(fi, fiPrev, fiNext, i, b, h, e);
    };

    vector<string> titles{ "Godunov", "MUSCL", "THINC_Godunov", "THINC_MUSCL" };

    for (int psy = 0; psy < PsyFunctions.size(); psy++) {
        cout << titles[psy] << " scheme" << endl;
        myfi << titles[psy] << " scheme" << endl;
        params.FlowInterpolationFunction = PsyFunctions[psy];

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

            vector<double> uStatic(params.cellCount+1, 0.1);
            function<vector<double>(int)> u = [=](int t05n)->vector<double>{
                return uStatic;
            };

            int T = (double)N / params.CFL;
            params.NTimeSteps = T;

            cout << "N" << N << "\t";
            myfi << "N" << N << "\t";
            for (int j = 0; j < jTmax; j++) {
                Solver1DOutput output(
                        true,
                        true,
                        true,
                        OUTPUT_PATH+"CalculationResults/" + titles[psy] + "/N" + std::to_string(N) + "_T" + std::to_string(j + 1) + ".txt");
                SolveTransportEquation1D(params, f, u, output);
                double error = errorL2(f, fexact, params.areaLength / params.cellCount);
                string errorLine = "error "+ to_string(error);
                output.printLine(errorLine);
                output.finish();
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
*/
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
/*
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
    Area1D params;

    // Scalar params
    params.areaLength = 1;
    params.uMax = 0.1;

    // Test specific params
    double beta = 3.5;
    double eps = 1e-4;
    params.FlowInterpolationFunction = [=](double fi, double fiPrev, double fiNext, int i, double h)->function<double(double)> {
        return PsyTHINCandMUSCL(fi, fiPrev, fiNext, i, beta, h, eps);
    };
    params.FlowInterpolationFunctionName = "Psy THINC + MUSCL";
    params.CFL = 0.3;
    int i = 8;
    int N = params.CFL * 10.0 * pow(2, i);
    params.cellCount = N;
    int T = (double) N / params.CFL;
    int j = 6;
    params.NTimeSteps = T * j;

    // scalarFunction init
    double L = N / 2;
    double R = N - 1;
    vector<double> f(N);
    initF(f, L, R);

    vector<double> uStatic(params.cellCount+1, 0.1);
    function<vector<double>(int)> u = [=](int t05n)->vector<double>{
        return uStatic;
    };

    Solver1DOutput nOut = noOutput();
    SolveTransportEquation1D(params, f, u, nOut);

    string debugFilePath =
            "C:\\Programing\\Projects\\DigitalGeometry\\Programs\\Output\\StandardResults\\THINC_MUSCL\\N768_T6.txt";
    bool testResult = test1DSolutionWithFile(f, debugFilePath, params.cellCount, 1e-6);

    cout << endl <<
         "------------------" << endl <<
         "Psy function: " << params.FlowInterpolationFunctionName << endl <<
         "cellCount: " << params.cellCount << " NTimeSteps: " << params.NTimeSteps << endl <<
         "CFL: " << params.CFL << " Area size: " << params.areaLength << endl <<
         "beta: " << beta << " eps: " << eps << " uMax: " << params.uMax << endl <<
         "------------------" << endl <<
         (testResult ? "TEST SUCCEEDED" : "TEST FAILED") << endl;
}*/

void test1DSolverStandard(){
    // Debug params
    THINC1DparamsDebug paramsDebug;

    // Scalar params
    double beta = 3.5;
    double eps = 1e-4;
    paramsDebug.area = 1;
    paramsDebug.u = 0.1;
    paramsDebug.eps = eps;
    paramsDebug.beta = beta;

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

    Solver1DParams params = getParamsFor(
            0.3,
            0.1,
            1.0,
            N,
            time,
            [=](F1D f1D, C1D c1D) -> function<double(double)> {
                return PsyTHINCandMUSCL(f1D, c1D, 3.5, 1e-4);
            },
            "Psy THINC + MUSCL"
            );

    VectorField1D u = getStaticVF1D(0.1, N+1);

    // scalarFunction init
    double L = N / 2;
    double R = N - 1;
    vector<double> f(N);
    initF(f, L, R);
    Area1D area1D(true, f);
    vector<double> fexact = f;

    vector<double> fStd = f;
    const vector<double>& fExStd = fexact;

    cout << "Computing with current solver" << endl;
    Solver1DOutput nOut = noOutput();
    SolveTransportEquation1D(area1D, u, params, nOut);
    cout << "Computing with standard solver" << endl;
    THINC1DDebug(paramsDebug, fStd, fExStd);
    /*for(int i=0; i<fStd.size(); i++)
        cout << i << "\t" << fStd[i] << endl;*/
    cout << "Comparing solutions" << endl;
    bool testResult = compare1DSolutions(f, fStd, params.cellCount, 0.0);

    cout << endl <<
         "------------------" << endl <<
         "Psy function: " << params.FlowInterpolationFunctionName << endl <<
         "cellCount: " << params.cellCount << " NTimeSteps: " << params.NTimeSteps << endl <<
         "CFL: " << params.CFL << " Area size: " << params.areaLength << endl <<
         "beta: " << beta << " eps: " << eps << " uPrimary: " << 0.1 << endl <<
         "------------------" << endl <<
         (testResult ? "TEST SUCCEEDED" : "TEST FAILED") << endl;
}