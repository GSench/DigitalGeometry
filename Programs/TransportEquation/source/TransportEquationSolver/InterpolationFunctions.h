

#ifndef TRANSPORTEQUATION_INTERPOLATION_FUNCTIONS
#define TRANSPORTEQUATION_INTERPOLATION_FUNCTIONS

#include <functional>
#include "Solver1D/Area1D.h"
#include "Solver1D/Cell1D.h"

using namespace std;

function<double(double)> PsyGodunov(double fi);
function<double(double)> PsyMUSCL(F1D f, Cell1D c);
function<double(double)> PsyTHINC(F1D f, Cell1D c, double beta);
function<double(double)> PsyTHINCandGodunov(F1D f, Cell1D c, double beta, double eps);
function<double(double)> PsyTHINCandMUSCL(F1D f, Cell1D c, double beta, double eps);
double getXforInterpolation(double x, double u, double t);

#endif TRANSPORTEQUATION_INTERPOLATION_FUNCTIONS
