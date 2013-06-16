/* Basear-se fortemente em http://www.speqmath.com/tutorials/matrix/matrix.html
 Como é uma template (pra poder instanciar matrizes de doubles, ints, etc),
 a definição não pode ser feita num .cpp. Tem que ser feita aqui mesmo. */

#ifndef MATRIX_H
#define	MATRIX_H

#include <cmath>
#include <iostream>
#include <cassert>
using namespace std;

template <class _MT> //_MT: matrix type
class Matrix {
private:
    int rows; //número 
    int cols;
    _MT** m_pMatrix; // pointer to a matrix with _MT type

public:

    /* Cria um objeto Matrix sem conteúdo */
    Matrix() {
        cout << "Construtor padrão" << endl;
        m_pMatrix = NULL;
        rows = 0;
        cols = 0;
    }

    /* Cria uma cópia do objeto Matrix orig */
    Matrix(const Matrix& orig) {
        rows = orig.rows;
        cols = orig.cols;
        m_pMatrix = new _MT*[rows];
        for (int r = 0; r < cols; r++) {
            m_pMatrix[r] = new _MT[cols];
            for (int c = 0; c < cols; c++)
                m_pMatrix[r][c] = orig.m_pMatrix[r][c]; //copy the values from the matrix orig
        }
    }

    /* Cria uma matriz nula com o tamanho fornecido */
    Matrix(const int row_count, const int column_count) {
        cout << "Construtor passando dimensão" << endl;
        assert(row_count > 0 && column_count > 0);
        rows = row_count;
        cols = column_count;
        m_pMatrix = new _MT*[rows];
        for (int r = 0; r < cols; r++) {
            m_pMatrix[r] = new _MT[cols];
            for (int c = 0; c < cols; c++)
                m_pMatrix[r][c] = 0; //fill in zeros for all values in the matrix
        }
    }

    virtual ~Matrix() {
        //clean up a allocated memory
        for (int r = 0; r < rows; r++)
            delete m_pMatrix[r];
        delete m_pMatrix;
        m_pMatrix = NULL;
    }

    /* index operator. Usage: myMatrixObj[row,col]; index are one-based. */
    _MT& operator()(const int r, const int c) {
        assert(m_pMatrix != NULL && r > 0 && r <= rows && c > 0 && c <= cols);
        return m_pMatrix[r - 1][c - 1];
    }

    /* index operator. Usage: myMatrixObj.get(row,col). Index are one-based.
     * Use this function if you only want to read from a const Matrix. */
    _MT get(const int r, const int c) const {
        assert(m_pMatrix != NULL && r > 0 && r <= rows && c > 0 && c <= cols);
        return m_pMatrix[r - 1][c - 1];
    }

    /* assignment operator */
    Matrix& operator=(const Matrix& a) {
        //se a matriz existir anteriormente, deleta ela.
        if (m_pMatrix) {
            for (int r = 0; r < rows; r++)
                delete m_pMatrix[r];
            delete m_pMatrix;
            m_pMatrix = NULL;
        }

        rows = a.rows;
        cols = a.cols;
        m_pMatrix = new _MT*[rows];
        for (int r = 0; r < rows; r++) {
            m_pMatrix[r] = new _MT[cols];
            for (int c = 0; c < cols; c++)
                m_pMatrix[r][c] = a.m_pMatrix[r][c]; //copy matrix
        }
        return *this;
    }

    /* add a value (elements wise) */
    Matrix& Add(const _MT v) {
        for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols; c++)
                m_pMatrix[r][c] += v;
        return *this;
    }


};

#endif	/* MATRIX_H */