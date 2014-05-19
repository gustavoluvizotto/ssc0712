/* Simple C++ Test
 * Para testar e ver as funcionalidades da Classe Matrix */

#include <stdlib.h>
#include "Matrix.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv) {

    cout << "Começando o teste..." << endl;

    Matrix A = Matrix(3, 3);

    cout << "Matrix A = Matrix(3,3)" << endl;
    A.Print();
    cout << endl;

    A = Matrix::Zeros(3, 3);
    cout << "A = Matrix::Zeros(3, 3)" << endl;
    A.Print();
    cout << endl;

    for (int r = 1; r <= 3; r++)
        for (int c = 1; c <= 3; c++)
            A(r, c) = r + c;
    cout << "Colocando alguns valores na matriz A: A(r,c)=r+c" << endl;
    A.Print();
    cout << endl;

    Matrix O = Matrix::Ones(3, 3);
    cout << "Matrix O = Matrix::Ones(3,3)" << endl;
    O.Print();
    cout << endl;

    Matrix D = Matrix::Diag(3);
    cout << "Matrix D = Matrix::Diag(3)" << endl;
    D.Print();
    cout << endl;

    D = Matrix::Diag(3, 9);
    cout << "D = Matrix::Diag(3, 9)" << endl;
    D.Print();
    cout << endl;


    Matrix R = Matrix::Rand(3, 3);
    cout << "Matrix R = Matrix::Rand(3,3)" << endl;
    R.Print();
    cout << endl;

    Matrix I = Matrix::Identity(4);
    cout << "Matrix I = Matrix::Identity(4)" << endl;
    I.Print();
    cout << endl;

    Matrix AmaisO = A + O;
    cout << "Matrix AmaisB = A+O" << endl;
    AmaisO.Print();
    cout << endl;

    cout << "\nUma série de cálculos matriciais legais\n"
            "Repare que não precisamos instanciar uma matriz\n"
            "para receber o valor das operações, pois as\n"
            "operações são todas sobrecarga de operadores\n"
            "retornando uma nova matriz:\n" << endl;

    cout << "(A+O).Print()" << endl;
    (A + O).Print();
    cout << endl;

    cout << "(A-O).Print()" << endl;
    (A - O).Print();
    cout << endl;

    cout << "(A + 10).Print()" << endl;
    (A + 10).Print();
    cout << endl;

    cout << "(10 + A).Print()" << endl;
    (10 + A).Print();
    cout << endl;

    cout << "(2 * A).Print()" << endl;
    (2 * A).Print();
    cout << endl;

    cout << "(A * 2).Print()" << endl;
    (A * 2).Print();
    cout << endl;

    cout << "(A / 2).Print()" << endl;
    (A / 2).Print();
    cout << endl;

    cout << "(-A).Print()" << endl;
    (-A).Print();
    cout << endl;

    cout << "Matrix::Ones(3,3) + Matrix::Diag(3,2)).Print()" << endl;
    (Matrix::Ones(3, 3) + Matrix::Diag(3, 2)).Print();
    cout << endl;

    cout << "Lembrando: R.Print():" << endl;
    R.Print();
    cout << endl;

    cout << "Matrix::Det(R) = " << Matrix::Det(R) << endl;
    cout << endl;

    Matrix E = Matrix::Rand(2, 4);
    cout << "Matrix E = Matrix::Rand(2,4)" << endl;
    E.Print();
    cout << endl;

    cout << "Matrix::Transpose(E)" << endl;
    Matrix::Transpose(E).Print();
    cout << endl;


    cout << "A = Matrix::Rand(3,3)" << endl;
    A = Matrix::Rand(3, 3);
    A.Print();
    cout << endl;

    cout << "B = Matrix::Rand(3,3)" << endl;
    Matrix B = Matrix::Rand(3, 3);
    B.Print();
    cout << endl;

    cout << "(A/B).Print()" << endl;
    (A / B).Print();
    cout << endl;

    cout << "(A * Inv(B)).Print()" << endl;
    (A * Matrix::Inv(B)).Print();
    cout << endl;

    cout << "A = Matrix::Rand(2,2)" << endl;
    A = Matrix::Rand(2, 2);
    A.Print();
    cout << endl;

    cout << "Matrix::Inv(A).Print()" << endl;
    Matrix::Inv(A).Print();
    cout << endl;

    cout << "A.Clean().Print()" << endl;
    A.Clean().Print();
    cout << endl;

    cout << "A.Print()  (veja que houve a alteração inline da matriz A, quer dizer, ela foi alterada!)" << endl;
    A.Print();
    cout << endl;

    cout << "A.Set(3).Print()" << endl;
    A.Set(3).Print();
    cout << endl;

    cout << "A.Print() (veja que a alteração também foi inline.)" << endl;
    A.Print();
    cout << endl;

    Matrix *L = new Matrix(100, 100);
    L->Print();
    delete L;
    
    return (EXIT_SUCCESS);
}

