#include "TESolver1DOutput.h"
#include "../Methods/OverEdgeFlow.h"
#include "../../Utils/TimeLogger.h"

using namespace std;
//TODO calculate flow over edge only once
template<typename Q, typename F>
void updateCell(Mesh<Q> &f,
                TESolver1DParams &p,
                OverEdgeFlow<Q,F>& flowCalculator){
    F fL = flowCalculator.calc(*f.prev(), f, p.getDt(), L);
    F fR = flowCalculator.calc(f, *f.next(), p.getDt(), R);
    F resultFlow = fL - fR;
    Q fNext = f.getQuantity() - (fR - fL)/f.dx();
    f.setQuantity(fNext);
}

template<typename Q, typename F>
void TESolverStep(Mesh<Q>& f,
                  TESolver1DParams& p,
                  OverEdgeFlow<Q,F>& flowCalculator){
    Mesh<Q>* fIter = &f;
    do {
        updateCell<Q,F>(*fIter, p, flowCalculator);
        fIter = fIter->next();
    }
    while (!fIter->isBorder());
    updateCell<Q,F>(*fIter, p, flowCalculator);
}

template<typename Q>
void TESolverPostProcessStep(Mesh<Q>& f,
                  //TESolver1DParams& p,
                  const function<void(Mesh<Q>&)>& postProcess){
    Mesh<Q>* fIter = &f;
    do {
        postProcess(*fIter);
        fIter = fIter->next();
    }
    while (!fIter->isBorder());
    postProcess(*fIter);
}

template<typename Q, typename F>
void SolveTransportEquation1D(Mesh<Q>& f,
                              TESolver1DParams& p,
                              OverEdgeFlow<Q,F>& flowCalculator,
                              TESolver1DOutput<Q> &output,
                              const function<void(Mesh<Q>&)>& postProcess
) {
    output.print(f, 0);
    for (int n = 0; n < p.getNTimeSteps(); n++) {
        TESolverStep<Q,F>(f, p, flowCalculator);
        f.apply();
        TESolverPostProcessStep<Q>(f, postProcess);
        f.apply();
        output.print(f, n+1);
    }
}