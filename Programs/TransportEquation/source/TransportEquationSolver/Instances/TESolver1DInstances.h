#ifndef TRANSPORTEQUATION_TESOLVER1DINSTANCES_H
#define TRANSPORTEQUATION_TESOLVER1DINSTANCES_H

#include <functional>
#include <string>
#include <vector>

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

class LineInterface {
public:
    virtual ~LineInterface() = default;
    virtual double operator[](int i) = 0;
    virtual void set(int i, double val) = 0;
    virtual int size() = 0;
};

C1D getCi(double dx, int i);

F1D getFi(LineInterface& f, int i);

U1D getUi(LineInterface& u, int i);

#endif //TRANSPORTEQUATION_TESOLVER1DINSTANCES_H