//
// Created by grigoriy.senchenok on 21.12.2021.
//

#ifndef TRANSPORTEQUATION_STANDARDSOLVER_H
#define TRANSPORTEQUATION_STANDARDSOLVER_H

#include <functional>
#include <vector>

using namespace std;

struct THINC1DparamsDebug {
    int cellCount = 20;
    double area = 1;
    int stepN = 100;
    double CFL = 0.3;
    double u = 0.1;
    double eps = 1e-4;
    double beta = 3.5;
    function<function<double(double)>(vector<double>, int, double, double, double)> PsyFunc;
};

function<double(double)> PsyGodunovDebug(const vector<double>&, int, double, double, double);
function<double(double)> PsyMUSCLDebug(const vector<double>&, int, double, double, double);
function<double(double)> PsyTHINCandGodunovDebug(const vector<double>&, int, double, double, double);
function<double(double)> PsyTHINCandMUSCLDebug(const vector<double>&, int, double, double, double);

double THINC1DDebug(const THINC1DparamsDebug&, vector<double>&, const vector<double>&);

#endif //TRANSPORTEQUATION_STANDARDSOLVER_H
