#include <stdlib.h>
#include <iostream>
#include "Point.h"
#include "Parameters.h"
using namespace std;

int main(int argc, char** argv) {
    Point<double> P1(7.1, 8.1);
    Point<double> P2(2.0, 2.0);
    Point<double> P3 = P1 * P2;
    
    P3.Print();
    P3 *= P2;
    P3.Print();

    (P3+P2).Print();
    
    return (EXIT_SUCCESS);
}

