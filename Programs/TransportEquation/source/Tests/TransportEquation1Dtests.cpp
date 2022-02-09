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
#include "../configs.h"

using namespace std;

void Solver1Dtests() {

    const string testFolder = downDir(CALCULATION_1D_OUTPUT_PATH, "Solver1Dtests");

    int iNmax = 9;
    int iNmin = 3;
    int jTmax = 6;

    Solver1DParams params;

    ofstream myfi;
    myfi.open(downDir(testFolder, "error.txt"));
    myfi << endl;

    double b = 3.5;
    double e = 1e-4;
    vector< function<function<double(double)>(F1D f1D, C1D c1D)> > PsyFunctions(4);
    PsyFunctions[0] = [=](F1D f1D, C1D c1D) -> function<double(double)> {
        return PsyGodunov(f1D.fi);
    };
    PsyFunctions[1] = [=](F1D f1D, C1D c1D) -> function<double(double)> {
        return PsyMUSCL(f1D, c1D);
    };
    PsyFunctions[2] = [=](F1D f1D, C1D c1D) -> function<double(double)> {
        return PsyTHINCandGodunov(f1D, c1D, b, e);
    };
    PsyFunctions[3] = [=](F1D f1D, C1D c1D) -> function<double(double)> {
        return PsyTHINCandMUSCL(f1D, c1D, b, e);
    };

    vector<string> titles{ "Godunov", "MUSCL", "THINC_Godunov", "THINC_MUSCL" };

    params.CFL = 0.3;
    params.areaLength = 1.0;
    double uPrimary = 0.1;

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
            params.dx = params.areaLength / params.cellCount;
            double L = N / 2;
            double R = N - 1;
            Area1D fArea(N, true);
            fArea.fillRightHalfWith(1);
            vector<double> fexact = fArea.getF();

            VectorField1D u = getStaticVF1D(0.1, N+1);

            int T = (double)N / params.CFL;
            params.NTimeSteps = T;
            params.dt = params.CFL * params.dx / uPrimary;

            cout << "N" << N << "\t";
            myfi << "N" << N << "\t";
            for (int j = 0; j < jTmax; j++) {
                Solver1DOutput output = minimal1DOutput(
                        downDir(
                                downDir(
                                        testFolder,  titles[psy]),
                                        "N" + to_string(N) + "_T" + to_string(j + 1) + ".txt"),
                        T);
                output.printHeader(params);
                SolveTransportEquation1D(fArea, u, params, output);
                double error = errorL2(fArea.getF(), fexact, params.dx);
                output.printError(error);
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
    Area1D area1D(N, true);
    area1D.fillRightHalfWith(1);
    vector<double> fexact = area1D.getF();

    vector<double> fStd = area1D.getF();
    const vector<double>& fExStd = fexact;

    cout << "Computing with current solver" << endl;
    Solver1DOutput nOut = noOutput();
    SolveTransportEquation1D(area1D, u, params, nOut);
    cout << "Computing with standard solver" << endl;
    THINC1DDebug(paramsDebug, fStd, fExStd);
    /*for(int i=0; i<fStd.size(); i++)
        cout << i << "\t" << fStd[i] << endl;*/
    cout << "Comparing solutions" << endl;
    bool testResult = compare1DSolutions(area1D.getF(), fStd, params.cellCount, 0.0);

    cout << endl <<
         "------------------" << endl <<
         "Psy function: " << params.FlowInterpolationFunctionName << endl <<
         "cellCount: " << params.cellCount << " NTimeSteps: " << params.NTimeSteps << endl <<
         "CFL: " << params.CFL << " Area size: " << params.areaLength << endl <<
         "beta: " << beta << " eps: " << eps << " uPrimary: " << 0.1 << endl <<
         "------------------" << endl <<
         (testResult ? "TEST SUCCEEDED" : "TEST FAILED") << endl;
}