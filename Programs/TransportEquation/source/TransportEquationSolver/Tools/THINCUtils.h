#include <functional>

double getGamma(double fiNext, double fiPrev);
double getAlpha(double fiNext, double fiPrev);
double getXiavg(double beta, double gamma, double fi);
bool calcCondition(double fiPrev, double fi, double fiNext, double eps);
std::function<double(double)> Fi(double beta, double gamma, double xiLeft, double deltaXi, double xiavg);