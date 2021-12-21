#include <vector>
#include <string>

#include "../InterpolationFunctions.h"

using namespace std;

struct THINC1Dparams {
    int cellCount = 20;
    double area = 1;
    int stepN = 100;
    double CFL = 0.3;
    double u = 0.1;
    double eps = 1e-4;
    double beta = 3.5;
    function<function<double(double)>(double, double, double, int, double, double, double)> PsyFunc =
            [&](double fi, double fiPrev, double fiNext, int i, double b, double h, double e)->function<double(double)> {
                return PsyTHINCandMUSCL(fi, fiPrev, fiNext, i, b, h, e);
            };
    string PsyFuncName = "Psy THINC + MUSCL";
};
