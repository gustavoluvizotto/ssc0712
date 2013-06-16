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
        cout << "Construtor a partir de uma Matrix" << endl;
        rows = orig.rows;
        cols = orig.cols;
        m_pMatrix = new _MT*[rows];
        for (int r = 0; r < rows; r++) {
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
        for (int r = 0; r < rows; r++) {
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
        cout << "Destrutor" << endl;
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

    /* assignment/clone operator. Funciona como se fosse um clone() */
    Matrix<_MT>& operator=(const Matrix<_MT>& a) {
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
        cout << "assignment/clone operator" << endl;
        return *this;
    }

    /* add a value (elements wise) */
    Matrix<_MT>& Add(const _MT v) {
        assert(m_pMatrix);
        for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols; c++)
                m_pMatrix[r][c] += v;
        cout << "add elements wise" << endl;
        return *this;
    }

    /* subtract a value (elements wise) */
    Matrix<_MT>& Subtract(const _MT v) {
        cout << "subtract elements wise" << endl;
        return Add(-v);
    }

    /* multiply a value (elements wise) */
    Matrix<_MT>& Multiply(const _MT v) {
        for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols; c++)
                m_pMatrix[r][c] *= v;
        cout << "multiply elements wise" << endl;
        return *this;
    }

    /* divide by a value (elements wise) */
    Matrix<_MT>& Divide(const _MT v) {
        for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols; c++)
                m_pMatrix[r][c] /= v;
        cout << "divide elements wise" << endl;
        return *this;
    }

    /* adição de 2 matrizes, retornando uma terceira matriz */
    friend Matrix<_MT> operator+(const Matrix<_MT>& a, const Matrix<_MT>& b) {
        cout << "operator+(Matrix&, Matrix&)" << endl;
        assert(a.rows == b.rows && a.cols == b.cols);
        Matrix<_MT> res(a.rows, a.cols);
        for (int r = 0; r < a.rows; r++)
            for (int c = 0; c < a.cols; c++)
                res.m_pMatrix[r][c] = a.m_pMatrix[r][c] + b.m_pMatrix[r][c];
        return res;
    }

    /* adição de Matrix com escalar (_MT), retornando uma terceira matriz */
    friend Matrix<_MT> operator+(const Matrix<_MT>& a, const _MT val) {
        cout << "operator+(Matrix&, scalar)" << endl;
        Matrix<_MT> res(a);
        res.Add(val);
        return res;
    }

    /* adição de escalar com Matrix, retornando uma terceira matrix */
    friend Matrix<_MT> operator+(const _MT val, const Matrix<_MT>& a) {
        cout << "operator+(scalar, Matrix&)" << endl;
        return a + val;
    }

    /* subtração de 2 matrizes, retornando uma terceira matriz */
    friend Matrix<_MT> operator-(const Matrix<_MT>& a, const Matrix<_MT>& b) {
        cout << "operator-(Matrix&, Matrix&)" << endl;
        assert(a.rows == b.rows && a.cols == b.cols);
        Matrix<_MT> res = a;
        for (int r = 0; r < a.rows; r++)
            for (int c = 0; c < a.cols; c++)
                res.m_pMatrix[r][c] -= b.m_pMatrix[r][c];
        return res;
    }

    /* subtração de matrizes e escalar (_MT), retornando uma terceira matriz */
    friend Matrix<_MT> operator-(const Matrix<_MT>& a, const _MT val) {
        cout << "operator-(Matrix&, scalar)" << endl;
        Matrix<_MT> res = a;
        res.Subtract(val);
        return res;
    }

    /* operador "menos" unário */
    friend Matrix<_MT> operator-(const Matrix& a) {
        cout << "operator- unário" << endl;
        Matrix<_MT> res(a);
        res.Multiply(-1);
        return res;
    }

    /* subtração de escalar (_MT) e matrizes, retornando uma terceira matriz */
    friend Matrix<_MT> operator-(const _MT val, const Matrix<_MT>& a) {
        cout << "operator-(scalar, Matrix&)" << endl;
        return -(a - val);
    }

    /* operador multiplicação. Retorna uma Matrix nova */
    friend Matrix<_MT> operator*(const Matrix<_MT>& a, const Matrix<_MT>& b) {
        cout << "operator*(Matrix&, Matrix&)" << endl;
        assert(a.cols == b.rows);
        Matrix<_MT> res(a.rows, b.cols);

        for (int r = 0; r < a.rows; r++)
            for (int c_res = 0; c_res < b.cols; c_res++)
                for (int c = 0; c < a.cols; c++)
                    res.m_pMatrix[r][c_res] += a.m_pMatrix[r][c] * b.m_pMatrix[c][c_res];
        return res;
    }

    /* multiplicação de matriz por escalar (_MT). Retorna uma Matrix nova */
    friend Matrix<_MT> operator*(const Matrix<_MT>& a, const _MT b) {
        cout << "operator*(Matrix&, scalar)" << endl;
        Matrix<_MT> res = a;
        res.Multiply(b);
        return res;
    }

    /* multiplicação de escalar (_MT) por matriz. Retorna uma Matrix nova */
    friend Matrix<_MT> operator*(const _MT b, const Matrix<_MT>& a) {
        cout << "operator*(scalar, Matrix&)" << endl;
        return a*b;
    }

    /* divisão matricial a/b. Retorna uma Matrix nova */
    friend Matrix<_MT> operator/(const Matrix<_MT>& a, const Matrix<_MT>& b) {
//        Matrix<_MT> res
    }

    /* print the contents of the matrix */
    void Print() const {
        int r, c;
        if (m_pMatrix != NULL) {
            printf("[");
            for (r = 0; r < rows; r++) {
                if (r > 0) {
                    cout << " ";
                }
                for (c = 0; c < cols - 1; c++) {
                    cout << m_pMatrix[r][c] << ", ";
                }
                if (r < rows - 1) {
                    cout << m_pMatrix[r][cols - 1] << ";" << endl;
                } else {
                    cout << m_pMatrix[r][cols - 1] << "]" << endl;
                }
            }
        } else {
            // matrix is empty
            cout << "[ ]" << endl;
        }
    }
};

#endif	/* MATRIX_H */