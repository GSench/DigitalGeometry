#ifndef TRANSPORTEQUATION_SOLVER1DINSTANCES_H
#define TRANSPORTEQUATION_SOLVER1DINSTANCES_H

#include <functional>
#include <string>

using namespace std;

struct C1D {
    double x;
    double dx;
    double xL;
    double xR;
};

C1D inverse(const C1D &c);

struct F1D {
    double fi;
    double fiPrev;
    double fiNext;
};

F1D inverse(const F1D &f);

struct U1D {
    double uL;
    double uR;
};

// TODO refactor class Solver1DParams
class Solver1DParams {
public:
    double CFL;
    double dt;
    double areaLength;
    int cellCount;
    int NTimeSteps;
    double dx;
    function<function<double(double)>(F1D f, C1D c)> FlowInterpolationFunction;
    string FlowInterpolationFunctionName;
};

class LineInterface {
public:
    virtual ~LineInterface() = default;
    virtual double operator[](int i) = 0;
    virtual void set(int i, double val) = 0;
    virtual int size() = 0;
};

C1D getCi(const Solver1DParams& p, int i);

F1D getFi(LineInterface& f, int i);

U1D getUi(LineInterface& u, int i);

Solver1DParams getParamsFor(double CFL, double uPrimary, double areaLength, int cellCount, int NTimeSteps,
                            const function<function<double(double)>(F1D f, C1D c)>& PsyFunc,
                            const string& PsyFuncName);

#endif //TRANSPORTEQUATION_SOLVER1DINSTANCES_H