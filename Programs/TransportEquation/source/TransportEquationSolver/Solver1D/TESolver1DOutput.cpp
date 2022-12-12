//
// Created by grigoriy.senchenok on 21.12.2021.
//

#include "TESolver1DOutput.h"

function<string(double)> doublePrinter() {
    return [=](double f) -> string {
        return to_string(f);
    };
}

function<string(RBState)> rbStatePrinter() {
    return [=](RBState q) -> string {
        return to_string(q.getVolumeFraction());
    };
}