//
// Created by GSench on 14.12.2021.
//

#include <math.h>
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

#include "TransportEquation1Dtests.h"
#include "../TransportEquationSolver/Solver1D/TESolver1D.h"
#include "../configs.h"
#include "Tests.h"
#include "../TransportEquationSolver/Methods/GodunovFlow.h"
#include "../TransportEquationSolver/Methods/TimeStepVelocity.h"

using namespace std;

void TE1DGodunovStripMoveTest() {
    const string TEST_TITLE = "TE1DGodunovStripMoveTest";
    const string testDir = initTest(TEST_TITLE, CALCULATION_TE1D_OUTPUT_PATH);

    GodunovFlow<double> GFlow;
    TESolver1DParams<double, Velocity&> params(0.3, 0.1, 1.0, 8, 10, GFlow);
    TESolver1DOutput<double, Velocity&> output(TERMINAL, 1, 1, doublePrinter());
    Quantity<double> f = generate1DMesh<double>(params.getCellCount(), params.getDx(), params.getDx()/2, 0.);
    f.fillQuantity(0, 4, 1.0);
    f.apply();
    Vector uVect(0.1);
    TimeStepVelocity uConst(uVect, uVect);
    Quantity<Velocity&> u = generate1DMesh<Velocity&>(params.getCellCount()+1, params.getDx(), 0, uConst);
    SolveTransportEquation1D(f, u, params, output);
    output.finish();
}
/*
void Solver1DStripMovementTest(){
    const string TEST_TITLE = "Solver1DStripMovementTest";
    const string testDir = initTest(TEST_TITLE, CALCULATION_TE1D_OUTPUT_PATH);

    TESolver1DParams params (
            0.3,
            0.1,
            1.0,
            64,
            200,
            [=](F1D f1D, C1D c1D) -> function<double(double)> {
                return PsyTHINCandGodunov(f1D, c1D, 3.5, 1e-4);
            }
    );
    cout << "Psy THINC + Godunov" << endl;

    TESolver1DOutput out = minimal1DOutput(
            downDir(
                    testDir,
                    "area_" + to_string(params.getCellCount()) + "_t_" + to_string(params.getNTimeSteps()) + ".txt"),
            params.getNTimeSteps());
    out.printHeader(params);

    Area1D f(params.getCellCount(), true);
    f.fillRightHalfWith(1);

    VectorField1D u = getStaticVF1D(0.1, params.getCellCount()+1);

    SolveTransportEquation1D(f, u, params, out);

}

void Solver1DStripBackMovementTest(){
    const string TEST_TITLE = "Solver1DStripBackMovementTest";
    const string testDir = initTest(TEST_TITLE, CALCULATION_TE1D_OUTPUT_PATH);

    TESolver1DParams params (
            0.3,
            0.1,
            1.0,
            64,
            200,
            [=](F1D f1D, C1D c1D) -> function<double(double)> {
                return PsyTHINCandGodunov(f1D, c1D, 3.5, 1e-4);
            }
    );
    cout << "Psy THINC + Godunov" << endl;

    TESolver1DOutput out = minimal1DOutput(
            downDir(
                    testDir,
                    "area_" + to_string(params.getCellCount()) + "_t_" + to_string(params.getNTimeSteps()) + ".txt"),
            params.getNTimeSteps());
    out.printHeader(params);

    Area1D f(params.getCellCount(), true);
    f.fillLeftHalfWith(1);

    VectorField1D u = getStaticVF1D(-0.1, params.getCellCount()+1);

    SolveTransportEquation1D(f, u, params, out);

}

void Solver1DJRStripMovementTest(){
    const string TEST_TITLE = "Solver1DJRStripMovementTest";
    const string testDir = initTest(TEST_TITLE, CALCULATION_TE1D_OUTPUT_PATH);

    TESolver1DParams params (
            0.7,
            1.0,
            16,
            16,
            10,
            [=](F1D f1D, C1D c1D) -> function<double(double)> {
                return PsyJRandGodunov(f1D, c1D, 1e-4);
            }
    );
    cout << "Psy JR + Godunov" << endl;

    TESolver1DOutput out = minimal1DOutput(
            downDir(
                    testDir,
                    "area_" + to_string(params.getCellCount()) + "_t_" + to_string(params.getNTimeSteps()) + ".txt"),
            params.getNTimeSteps());
    out.printHeader(params);

    Area1D f(params.getCellCount(), true);
    f.fillRightHalfWith(1);

    RBVectorField1D u(-1.0, -1.0);

    SolveTransportEquationRBJR1D(f, u, params, out);
    out.finish();
}

void Solver1Dtests() {
    const string TEST_TITLE = "Solver1Dtests";
    const string testDir = initTest(TEST_TITLE, CALCULATION_TE1D_OUTPUT_PATH);

    int iNmax = 9;
    int iNmin = 3;
    int jTmax = 6;

    ofstream myfi;
    myfi.open(downDir(testDir, "error.txt"));
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

    double CFL = 0.3;
    double areaLength = 1.0;
    double uPrimary = 0.1;

    for (int psy = 0; psy < PsyFunctions.size(); psy++) {
        cout << titles[psy] << " scheme" << endl;
        myfi << titles[psy] << " scheme" << endl;

        cout << " \t";
        for (int j = 0; j < jTmax; j++)
            cout << "T" << (j + 1) << "\t";
        cout << endl;
        myfi << " \t";
        for (int j = 0; j < jTmax; j++)
            myfi << "T" << (j + 1) << "\t";
        myfi << endl;

        for (int i = iNmin; i < iNmax; i++) {
            int N = CFL * 10.0 * pow(2, i); //CFL*10 чтобы N был кратен CFL
            double L = N / 2;
            double R = N - 1;
            Area1D fArea(N, true);
            fArea.fillRightHalfWith(1);
            vector<double> fexact = fArea.getF();

            VectorField1D u = getStaticVF1D(0.1, N+1);

            int T = (double)N / CFL;

            TESolver1DParams params(
                    CFL,
                    uPrimary,
                    areaLength,
                    N,
                    T,
                    PsyFunctions[psy]
                    );

            cout << "N" << N << "\t";
            myfi << "N" << N << "\t";
            for (int j = 0; j < jTmax; j++) {
                TESolver1DOutput output = minimal1DOutput(
                        downDir(
                                downDir(
                                        testDir,  titles[psy]),
                                        "N" + to_string(N) + "_T" + to_string(j + 1) + ".txt"),
                        T);
                output.printHeader(params);
                SolveTransportEquation1D(fArea, u, params, output);
                double error = errorL2(fArea.getF(), fexact, params.getDx());
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
*/