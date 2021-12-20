#include <vector>
#include <string>

#include "../InterpolationFunctions.h"

using namespace std;

struct Solver2Dparams {
    int cellCount = 20;
    double area = 1;
    int stepN = 100;
    double CFL = 0.3;
    double eps = 1e-4;
    double beta = 3.5;
    std::string resultFilePath = "Solver2DOutput.txt";
    function<function<double(double)>(vector<double>, int, double, double, double)> PsyFunc =
            [&](const vector<double>& f, int i, double b, double h, double e)->function<double(double)> {
                return PsyTHINCandMUSCL(f, i, b, h, e);
            };
};
