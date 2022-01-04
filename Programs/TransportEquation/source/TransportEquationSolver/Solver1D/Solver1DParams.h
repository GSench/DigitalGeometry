#include <vector>
#include <string>

#include "../InterpolationFunctions.h"

using namespace std;

class Solver1DParams {
private:
    double dx = 0;
    double dt = 0;
public:
    int cellCount = 20;
    double area = 1;
    int stepN = 100;
    double CFL = 0.3;
    double u = 0.1;
    bool periodicBoundaries = true;
    function<function<double(double)>(double, double, double, int, double)> PsyFunc =
            [=](double fi, double fiPrev, double fiNext, int i, double h)->function<double(double)> {
                return PsyTHINCandMUSCL(fi, fiPrev, fiNext, i,  3.5, h, 1e-4);
            };
    string PsyFuncName = "Psy THINC + MUSCL";
    double h() {
        if(dx==0) dx = area/cellCount;
        return dx;
    }
    double timeStep(){
        if(dt==0) dt = CFL * h() / u;
        return dt;
    }
};
