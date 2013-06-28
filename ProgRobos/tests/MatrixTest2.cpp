#include <stdlib.h>
#include "Matrix.h"
#include <iostream>
using namespace std;

class T1 {
private:
    Matrix A;

public:

    T1() {
        A = Matrix::Rand(2, 2);
        A.Print();
    }

    Matrix& m1() {
        return A; //retorna uma referência!!!
    }

    void Imprime() {
        A.Print();
    }
};

int main(int argc, char** argv) {
    T1 obj;

    Matrix &RA = obj.m1();

    RA.Print();

    cout << "\n" << endl;
    RA.Add(1);
    RA.Print();
    obj.Imprime();

    return (EXIT_SUCCESS);
}

