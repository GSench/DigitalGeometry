//
// Created by grigoriy.senchenok on 28.01.2023.
//

#include <iostream>
#include "UTVector.h"
#include "../../math/VectorPrefabs.h"
#include "../UnitTestsLauncher.h"

int testVector(){
    string testTitle = "Vector";
    startTestMsg(testTitle);
    Vector a(0.0, 1.0, 1.0);
    Vector b(1.0, 0.0);
    Vector c = a*4 + 3*b;
    c+=b;
    c/=2;
    c+=unit(c);
    if(c[X]!=3.0){
        cout << "c[X]!=3.0; c[X]=" << c[X] << endl;
        cout << "c.dim = " << c.dim << endl;
        for(int i=0; i<c.dim; i++) cout << "c["<<i<<"]="<<c[i]<<";  ";
        cout << endl;
        errorTestMsg(testTitle);
        return 1;
    }
    if(c[Y]!=3.0){
        cout << "c[Y]!=3.0; c[Y]=" << c[Y] << endl;
        cout << "c.dim = " << c.dim << endl;
        for(int i=0; i<c.dim; i++) cout << "c["<<i<<"]="<<c[i]<<";  ";
        cout << endl;
        errorTestMsg(testTitle);
        return 2;
    }
    if(c[Z]!=3.0){
        cout << "c[Z]!=3.0; c[Z]=" << c[Z] << endl;
        cout << "c.dim = " << c.dim << endl;
        for(int i=0; i<c.dim; i++) cout << "c["<<i<<"]="<<c[i]<<";  ";
        cout << endl;
        errorTestMsg(testTitle);
        return 3;
    }
    successTestMsg(testTitle);
    return 0;
}
