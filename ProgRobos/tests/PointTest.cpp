#include <stdlib.h>
#include <iostream>
#include "Point.h"
#include "Parameters.h"
using namespace std;

int main(int argc, char** argv) {
    //    Point<double> P1(7.1, 8.1);
    //    Point<double> P2(2.0, 2.0);
    //    Point<double> P3 = P1 * P2;
    //    
    //    P3.Print();
    //    P3 *= P2;
    //    P3.Print();
    //
    //    (P3+P2).Print();

    Point<int> P4(3, 3);
    PRINT(P4.argument());

    Point<int> P5(-3, 3);
    PRINT(P5.argument());

    Point<int> P6(-3, -3);
    PRINT(P6.argument());

    Point<int> P7(3, -3);
    PRINT(P7.argument());

    Point<int> P8(3, 0);
    PRINT(P8.argument());

    return (EXIT_SUCCESS);
}