
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include "Matrix.h"
using namespace std;

int main(int argc, char** argv) {
    Matrix<double> M1(2, 2);
    
    M1(1,1) = 1;
    M1(1,2) = 2;
    M1(2,1) = 3;
    M1(2,2) = 4;
    
    (M1*3).Print();

    return (EXIT_SUCCESS);
}
