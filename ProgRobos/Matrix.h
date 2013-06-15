/* Fortemente baseada em http://www.speqmath.com/tutorials/matrix/matrix.html
 Como é uma template (pra poder instanciar matrizes de doubles, ints, etc),
 a definição não pode ser feita num .cpp. Tem que ser feita aqui mesmo. */

#ifndef MATRIX_H
#define	MATRIX_H

#include <cmath>
#include <iostream>
using namespace std;

template <class T2>
class Matrix {
private:
    int rows;
    int cols;
    T2** m_pMatrix; // pointer to a matrix with T2 type

public:
    Matrix() {
        cout << "Construtor Matrix()" << endl;
    }
    
    Matrix(const Matrix& orig) {}
    virtual ~Matrix() {}
    
    static T2 Det(const Matrix& a) {
        return 0;
    }
private:

};

#endif	/* MATRIX_H */
