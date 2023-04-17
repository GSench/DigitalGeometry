//
// Created by grigoriy.senchenok on 21.12.2021.
//

#include "TESolver1DOutput.h"

function<string(double)> doublePrinter() {
    return [=](double f) -> string {
        return to_string(f);
    };
}

function<string(SQuantity)> rbStatePrinter() {
    return [=](SQuantity q) -> string {
        return to_string(q.getVolumeFraction());
    };
}

function<string(GSQuantity)> gsQuantityPrinter() {
    return [=](GSQuantity q) -> string {
        //return to_string(q.density());
        return '{'
            + to_string(q.volumeFraction()) + ','
            + to_string(q.velocity()) + ','
            + to_string(q.density()) + ','
            + to_string(q.pressure())
            +'}';
    };
}