//
// Created by grigoriy.senchenok on 15.12.2021.
//

#ifndef TRANSPORTEQUATION_VECTOR_H
#define TRANSPORTEQUATION_VECTOR_H

#include <vector>

#include "Constants.h"

using namespace std;

class Vector {
private:
    vector<double> vals;
    int dim;
public:

    explicit Vector(const vector<double>& vals): vals(vals), dim(vals.size()) {}

    Vector(double x, double y, double z) : vals(3), dim(3) {
        vals[X]=x; vals[Y]=y; vals[Z]=z;
    }
    Vector(double x, double y) : vals(2), dim(2) {
        vals[X]=x; vals[Y]=y;
    }
    explicit Vector(double x) : vals(1), dim(1) {
        vals[X]=x;
    }
    explicit Vector(int dim) : vals(dim, 0), dim(dim) {}

    Vector(int dim, double val) : vals(dim, val), dim(dim) {}

    int getDim() const {
        return dim;
    }

    double operator [](int i) const {
        if(i>=dim) return 0;
        return vals[i];
    }

    // Vector operations

    Vector operator+(const Vector& v) const {
        vector<double> r(max(dim, v.getDim()));
        for(int i=0; i<r.size(); i++) r[i] = (*this)[i]+v[i];
        return Vector(r);
    }

    void operator+=(const Vector& v) {
        for(int i=0; i<dim; i++) vals[i]+=v[i];
    }

    Vector operator-(const Vector& v) const {
        vector<double> r(max(dim, v.getDim()));
        for(int i=0; i<r.size(); i++) r[i] = (*this)[i]-v[i];
        return Vector(r);
    }

    void operator-=(const Vector& v) {
        for(int i=0; i<dim; i++) vals[i]-=v[i];
    }

    // Scale operations

    Vector operator*(double s) const {
        vector<double> r = vals;
        for(double & x : r) x *= s;
        return Vector(r);
    }

    friend Vector operator*(double s, const Vector& v) {
        vector<double> r = v.vals;
        for(double & x : r) x *= s;
        return Vector(r);
    }

    void operator*=(double s) {
        for(double & x : vals) x *= s;
    }

    Vector operator/(double s) const {
        vector<double> r = vals;
        for(double & x : r) x /= s;
        return Vector(r);
    }

    void operator/=(double s) {
        for(double & x : vals) x /= s;
    }

};

inline Vector zero(int dim){
    return Vector(dim);
}

inline Vector zero(const Vector& dimVector){
    return zero(dimVector.getDim());
}

inline Vector unit(int dim){
    return {dim, 1.0};
}

inline Vector unit(const Vector& dimVector){
    return unit(dimVector.getDim());
}

#endif //TRANSPORTEQUATION_VECTOR_H
