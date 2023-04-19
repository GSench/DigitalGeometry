#include "TESolver1DOutput.h"
#include "../Methods/OverEdgeFlow.h"
#include "../Methods/FlowMachine.h"
#include "../../Utils/TimeLogger.h"

using namespace std;
//TODO calculate flow over edge only once
template<typename Q, typename F>
void updateCell(Mesh<Q> &f,
                const TESolver1DParams &p,
                const OverEdgeFlow<Q,F>& flowCalculator,
                const FlowMachine<Q,F>& flowMachine
){
    vector<F> fL = flowCalculator.calc(*(f.prev()), f, p.getDt(), L);
    vector<F> fR = flowCalculator.calc(f, *(f.next()), p.getDt(), R);
    Q fNext = flowMachine.calculateCell(f.getQuantity(), fL,fR, p);
    f.setQuantity(fNext);
}

template<typename Q, typename F>
void TESolverStep(Mesh<Q>& f,
                  const TESolver1DParams& p,
                  const OverEdgeFlow<Q,F>& flowCalculator,
                  const FlowMachine<Q,F>& flowMachine
){
    Mesh<Q>* fIter = &f;
    do {
        updateCell<Q,F>(*fIter, p, flowCalculator, flowMachine);
        fIter = fIter->next();
    }
    while (!fIter->isBorder());
    updateCell<Q,F>(*fIter, p, flowCalculator, flowMachine);
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
                              const TESolver1DParams& p,
                              const OverEdgeFlow<Q,F>& flowCalculator,
                              const FlowMachine<Q,F>& flowMachine,
                              TESolver1DOutput<Q> &output,
                              bool usePostProcess,
                              const function<void(Mesh<Q>&)>& postProcess
) {
    output.print(f, 0);
    for (int n = 0; n < p.getNTimeSteps(); n++) {
        TESolverStep<Q,F>(f, p, flowCalculator, flowMachine);
        f.apply();
        if(usePostProcess) {
            TESolverPostProcessStep<Q>(f, postProcess);
            f.apply();
        }
        output.print(f, n+1);
    }
}