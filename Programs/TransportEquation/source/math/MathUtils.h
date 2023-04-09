
#include <functional>
#include <vector>

using namespace std;

double clamp(double x,double lower,double upper);
double minmod(double x,double y);
template<typename T>int sgn(T val);
function<double(double)> linearTransform(const function<double(double)> &f,
                                         double dx, double kx, double dy, double ky);
function<double(double)> fInverseX(const function<double(double)> &f);
function<double(double)> fMoveX(const function<double(double)> &f, double dx);
double errorL2(vector<double> f, const vector<double>& fexact, double h);
template <typename T> T avg(const vector<T>& vals){
    if(vals.empty()) return T(0);
    T sum = T(0);
    for(T v: vals) sum+=v;
    return sum / vals.size();
}
template <typename T> T wavg(const vector<T>& vals, const vector<double>& weights){
    if(vals.empty() || vals.size() != weights.size()) return T(0);
    T sum = T(0);
    double totalWeight = 0;
    for(int i=0; i<vals.size(); i++){
        sum+=vals[i] * weights[i];
        totalWeight += weights[i];
    }
    if(totalWeight==0) return T(0);
    return sum / totalWeight;
}