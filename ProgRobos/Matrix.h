/* Fortemente baseada em http://www.speqmath.com/tutorials/matrix/matrix.html */

#ifndef MATRIX_H
#define	MATRIX_H

#include <cmath>
#include <iostream>
#include <cassert>
#include <ctime>
#include <sys/time.h>
#include <cstdlib>
using namespace std;

class Matrix {
private:
    int rows; //número 
    int cols;
    double** m_pMatrix; // pointer to a matrix with double type

public:

    /* Cria um objeto Matrix sem conteúdo */
    Matrix() {
        m_pMatrix = NULL;
        rows = 0;
        cols = 0;
    }

    /* Cria uma cópia do objeto Matrix orig */
    Matrix(const Matrix& orig) {
        rows = orig.rows;
        cols = orig.cols;
        m_pMatrix = new double*[rows];
        for (int r = 0; r < rows; r++) {
            m_pMatrix[r] = new double[cols];
            for (int c = 0; c < cols; c++)
                m_pMatrix[r][c] = orig.m_pMatrix[r][c]; //copy the values from the matrix orig
        }
    }

    /* Cria uma matriz nula com o tamanho fornecido */
    Matrix(const int row_count, const int column_count) {
        assert(row_count > 0 && column_count > 0);
        rows = row_count;
        cols = column_count;
        m_pMatrix = new double*[rows];
        for (int r = 0; r < rows; r++) {
            m_pMatrix[r] = new double[cols];
            for (int c = 0; c < cols; c++)
                m_pMatrix[r][c] = 0; //fill in zeros for all values in the matrix
        }
    }

    virtual ~Matrix() {
        //clean up a allocated memory
        for (int r = 0; r < rows; r++)
            delete[] m_pMatrix[r];
        delete[] m_pMatrix;
        m_pMatrix = NULL;
    }

    /* index operator. Usage: myMatrixObj[row,col]; index are one-based. */
    double& operator()(const int r, const int c) {
        assert(m_pMatrix != NULL); //&& r > 0 && r <= rows && c > 0 && c <= cols);
        return m_pMatrix[r][c];
    }

    /* index operator. Usage: myMatrixObj.get(row,col). Index are one-based.
     * Use this function if you only want to read from a const Matrix. */
    double get(const int r, const int c) const {
        assert(m_pMatrix != NULL && r > 0 && r <= rows && c > 0 && c <= cols);
        return m_pMatrix[r - 1][c - 1];
    }

    /* assignment/clone operator. Funciona como se fosse um clone() */
    Matrix& operator=(const Matrix& a) {
        //se a matriz existir anteriormente, deleta ela.
        if (m_pMatrix) {
            for (int r = 0; r < rows; r++)
                delete[] m_pMatrix[r];
            delete[] m_pMatrix;
            m_pMatrix = NULL;
        }
        rows = a.rows;
        cols = a.cols;
        m_pMatrix = new double*[rows];
        for (int r = 0; r < rows; r++) {
            m_pMatrix[r] = new double[cols];
            for (int c = 0; c < cols; c++)
                m_pMatrix[r][c] = a.m_pMatrix[r][c]; //copy matrix
        }
        return *this;
    }

    /**
     * Retorna a mesma matriz, só que com seus elementos acrescidos de val
     * @param val valor a ser adicionado aos elementos da matriz.
     * @return a mesma matriz, só que com seus elementos acrescidos de val
     */
    Matrix& Add(const double val) {
        assert(m_pMatrix);
        for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols; c++)
                m_pMatrix[r][c] += val;
        return *this;
    }

    /**
     * Retorna a mesma matriz, só que com seus elementos subtraídos de val
     * @param val valor a ser subtraído aos elementos da matriz.
     * @return a mesma matriz, só que com seus elementos subtraídos de val
     */
    Matrix& Subtract(const double val) {
        return Add(-val);
    }

    /**
     * Retorna a mesma matriz, só que com todos os seus elementos multiplicados por val
     * @param val número que multiplicará todos os elementos da matriz
     * @return a mesma matriz com seus elementos multiplicados por val
     */
    Matrix& Multiply(const double val) {
        for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols; c++)
                m_pMatrix[r][c] *= val;
        return *this;
    }

    /**
     * Retorna a mesma matriz, só que com todos os seus elementos divididos por val
     * @param val
     * @return a mesma matriz, com todos os seus elementos divididos por val
     */
    Matrix& Divide(const double val) {
        if (val != 0) {
            for (int r = 0; r < rows; r++)
                for (int c = 0; c < cols; c++)
                    m_pMatrix[r][c] /= val;
            return *this;
        }
    }

    /**
     * Seta todos os elementos da matriz com o valor val passado como parâmetro
     * @param val double escolhido para preencher a matriz
     * @return a mesma matriz, só que com todos os seus elementos preechidos com val
     */
    Matrix& Set(const double val) {
        for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols; c++)
                m_pMatrix[r][c] = val;
        return *this;
    }

    /**
     * Seta todos os elementos da matriz com zero (0).
     * @return a mesma matriz, só que com todos os seus elementos zerados.
     */
    Matrix& Clean() {
        return Set(0);
    }

    /* adição de 2 matrizes, retornando uma nova matriz */
    friend Matrix operator+(const Matrix& a, const Matrix& b) {
        assert(a.rows == b.rows && a.cols == b.cols);
        Matrix res(a.rows, a.cols);
        for (int r = 0; r < a.rows; r++)
            for (int c = 0; c < a.cols; c++)
                res.m_pMatrix[r][c] = a.m_pMatrix[r][c] + b.m_pMatrix[r][c];
        return res;
    }

    /* adição de Matrix com escalar, retornando uma nova matriz */
    friend Matrix operator+(const Matrix& a, const double val) {
        Matrix res(a);
        res.Add(val);
        return res;
    }

    /* adição de escalar com Matrix, retornando uma nova matrix */
    friend Matrix operator+(const double val, const Matrix& a) {
        return a + val;
    }

    /* subtração de 2 matrizes, retornando uma nova matriz */
    friend Matrix operator-(const Matrix& a, const Matrix& b) {
        assert(a.rows == b.rows && a.cols == b.cols);
        Matrix res = a;
        for (int r = 0; r < a.rows; r++)
            for (int c = 0; c < a.cols; c++)
                res.m_pMatrix[r][c] -= b.m_pMatrix[r][c];
        return res;
    }

    /* subtração de matrizes e escalar, retornando uma nova matriz */
    friend Matrix operator-(const Matrix& a, const double val) {
        Matrix res = a;
        res.Subtract(val);
        return res;
    }

    /* operador "menos" unário. Retorna uma nova matriz. */
    friend Matrix operator-(const Matrix& a) {
        Matrix res(a);
        res.Multiply(-1);
        return res;
    }

    /* subtração de escalar e matrizes, retornando uma nova matriz */
    friend Matrix operator-(const double val, const Matrix& a) {
        return -(a - val);
    }

    /* operador multiplicação. Retorna uma nova Matrix */
    friend Matrix operator*(const Matrix& a, const Matrix& b) {
        assert(a.cols == b.rows);
        Matrix res(a.rows, b.cols);

        for (int r = 0; r < a.rows; r++)
            for (int c_res = 0; c_res < b.cols; c_res++)
                for (int c = 0; c < a.cols; c++)
                    res.m_pMatrix[r][c_res] += a.m_pMatrix[r][c] * b.m_pMatrix[c][c_res];
        return res;
    }

    /* multiplicação de matriz por escalar. Retorna uma nova Matrix */
    friend Matrix operator*(const Matrix& a, const double b) {
        Matrix res = a;
        res.Multiply(b);
        return res;
    }

    /* multiplicação de escalar por matriz. Retorna uma Matrix nova */
    friend Matrix operator*(const double b, const Matrix& a) {
        return a*b;
    }

    /* divisão matricial a/b := a*inv(b). Retorna uma Matrix nova */
    friend Matrix operator/(const Matrix& a, const Matrix& b) {
        assert(b.rows == b.cols && a.cols == b.rows);
        Matrix res(a.rows, a.cols);
        res = a * Inv(b);
        return res;
    }

    /* divisão de matriz por escalar. Retorna uma Matrix nova */
    friend Matrix operator/(const Matrix& a, const double b) {
        assert(a.rows == a.cols);
        Matrix res(a);
        res.Divide(b);
        return res;
    }

    /**
     * retorna uma nova matriz, só que reduzida da 'this': sem row e col.
     * @param row linha a ser removida
     * @param col coluna a ser removida
     * @return uma nova matriz, porém reduzida da linha e coluna fornecidas
     */
    Matrix Minor(const int row, const int col) const {
        assert(row > 0 && row <= rows && col > 0 && col <= cols);
        Matrix res(rows - 1, cols - 1);

        //copy the content of the matrix to the minor, except the selected
        for (int r = 1; r <= (rows - (row == rows)); r++)
            for (int c = 1; c <= (cols - (col == cols)); c++)
                res(r - (r > row), c - (c > col)) = m_pMatrix[r - 1][c - 1];

        return res;
    }

    /* get the number of rows */
    int GetRows() const {
        return rows;
    }

    /* get the number of cols */
    int GetCols() const {
        return cols;
    }

    /**
     * print the contents of the matrix
     */
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

    /**
     * returns a matrix with all-ones
     * @param rows number of rows
     * @param cols number of columns
     * @return a Matrix cols x rows sized with ones as values
     */
    static Matrix Ones(const int rows, const int cols) {
        Matrix res = Matrix(rows, cols);

        for (int r = 1; r <= rows; r++)
            for (int c = 1; c <= cols; c++)
                res(r, c) = 1;
        return res;
    }

    /**
     * returns a zero matrix
     * @param rows number of rows
     * @param cols number of columns
     * @return a Matrix cols x rows sized with zeros as values
     */
    static Matrix Zeros(const int rows, const int cols) {
        return Matrix(rows, cols);
    }

    /**
     * returns a diagonal matrix
     * @param n number of rows = columns
     * @return a diagonal matrix n x n sized with ones at the diagonal
     */
    static Matrix Diag(const int n) {
        Matrix res = Matrix(n, n);
        for (int i = 1; i <= n; i++)
            res(i, i) = 1;
        return res;
    }

    /**
     * returns a diagonal-valued matrix
     * @param n number of rows = columns
     * @param val valor a ser colocado na diagonal
     * @return a diagonal matrix n x n sized with val at the diagonal
     */
    static Matrix Diag(const int n, const double val) {
        Matrix res = Matrix(n, n);
        for (int i = 1; i <= n; i++)
            res(i, i) = val;
        return res;
    }

    /**
     * returns a (n x n) identity matrix
     * @param n order of identity matrix
     * @return Identity matrix n x n
     */
    static Matrix Identity(const int n) {
        return Matrix::Diag(n);
    }

    /**
     * returns a diagonal matrix
     * @param v a vector
     * @return a diagonal matrix with the given vector v on the diagonal
     */
    static Matrix Diag(const Matrix& v) {
        assert((v.GetCols() == 1 || v.GetRows() == 1) && "Parameter for diag must be a vector");
        Matrix res;
        if (v.GetCols() == 1) { // a matriz v dada é um vetor coluna
            int rows = v.GetRows();
            res = Matrix(rows, rows);

            //copy vector values
            for (int r = 1; r <= rows; r++)
                res(r, r) = v.get(r, 1);
        } else { // a matriz v dada é um vetor linha
            int cols = v.GetCols();
            res = Matrix(cols, cols);

            //copy vector values
            for (int c = 1; c <= cols; c++)
                res(c, c) = v.get(1, c);
        }
        return res;
    }

    /**
     * Retorna uma nova matriz, que é a transposta da fornecida por referência
     * @param a matriz fornecida por referência
     * @return uma nova matriz, que é a transposta da matriz a
     */
    static Matrix Transpose(const Matrix& a) {
        Matrix res(a.GetCols(), a.GetRows());
        for (int r = 1; r <= a.GetRows(); r++)
            for (int c = 1; c <= a.GetCols(); c++)
                res(c, r) = a.get(r, c);
        return res;
    }

    /**
     * Cria uma matriz randômica
     * @param rows número de linhas da matriz
     * @param cols número de colunas da matriz
     * @return uma nova matriz randômica
     */
    static Matrix Rand(const int rows, const int cols) {
        assert(rows >= 1 && cols >= 1 && "# de linhas ou colunas tem que ser positivo");
        Matrix res = Matrix(rows, cols);
        struct timeval tv;
        gettimeofday(&tv, NULL);
        srand(tv.tv_usec);
        for (int r = 1; r <= rows; r++)
            for (int c = 1; c <= cols; c++)
                res(r, c) = rand() % 6 - 2;
        return res;
    }

    /**
     * returns the determinant of a Matrix
     * @param a input Matrix
     * @return determinant of the Matrix a
     */
    static double Det(const Matrix& a) {
        double d = 0; // value of the determinant
        int rows = a.GetRows();
        int cols = a.GetRows();
        assert(rows == cols && "Must give a square matrix!!");

        // this is a square matrix
        if (rows == 1) {
            // this is a 1 x 1 matrix
            d = a.get(1, 1);
        } else if (rows == 2) {
            // this is a 2 x 2 matrix
            // the determinant of [a11,a12;a21,a22] is det = a11*a22-a21*a12
            d = a.get(1, 1) * a.get(2, 2) - a.get(2, 1) * a.get(1, 2);
        } else {
            // this is a matrix of 3 x 3 or larger
            for (int c = 1; c <= cols; c++) {
                Matrix M = a.Minor(1, c);
                //d += pow(-1, 1+c) * a(1, c) * Det(M);
                d += (c % 2 + c % 2 - 1) * a.get(1, c) * Det(M); // faster than with pow()
            }
        }
        return d;
    }

    /* swap two values */
    static void Swap(double& a, double& b) {
        double temp = a;
        a = b;
        b = temp;
    }

    /**
     * returns the inverse of Matrix<double> a
     * @param a Matrix<double>, obrigatoriamente <double>
     * @return Inversa da matriz a. Importante: obrigatoriamente retorna uma matriz <double>
     */
    static Matrix Inv(const Matrix& a) {
        Matrix res;
        double d = 0; // value of the determinant
        int rows = a.GetRows();
        int cols = a.GetRows();

        d = Det(a);
        assert(d != 0 && "Determinante tem que ser diferente de 0");
        assert(rows == cols && "A matriz tem que ser quadrada");

        // this is a square matrix
        if (rows == 1) {
            // this is a 1 x 1 matrix
            res = Matrix(rows, cols);
            res(1, 1) = 1.0 / a.get(1, 1);
        } else if (rows == 2) {
            // this is a 2 x 2 matrix
            res = Matrix(rows, cols);
            res(1, 1) = a.get(2, 2);
            res(1, 2) = -a.get(1, 2);
            res(2, 1) = -a.get(2, 1);
            res(2, 2) = a.get(1, 1);
            res = (1.0 / d) * res;
        } else {
            // this is a matrix of 3 x 3 or larger
            // calculate inverse using gauss-jordan elimination
            //   http://mathworld.wolfram.com/MatrixInverse.html
            //   http://math.uww.edu/~mcfarlat/inverse.htm
            res = Diag(rows); // a diagonal matrix with ones at the diagonal
            Matrix ai = a; // make a copy of Matrix a

            for (int c = 1; c <= cols; c++) {
                // element (c, c) should be non zero. if not, swap content
                // of lower rows
                int r;
                for (r = c; r <= rows && ai(r, c) == 0; r++) {
                }
                if (r != c) {
                    // swap rows
                    for (int s = 1; s <= cols; s++) {
                        Matrix::Swap(ai(c, s), ai(r, s));
                        Matrix::Swap(res(c, s), res(r, s));
                    }
                }

                // eliminate non-zero values on the other rows at column c
                for (int r = 1; r <= rows; r++) {
                    if (r != c) {
                        // eleminate value at column c and row r
                        if (ai(r, c) != 0) {
                            double f = -ai(r, c) / (double) ai(c, c);

                            // add (f * row c) to row r to eleminate the value
                            // at column c
                            for (int s = 1; s <= cols; s++) {
                                ai(r, s) += f * ai(c, s);
                                res(r, s) += f * res(c, s);
                            }
                        }
                    } else {
                        // make value at (c, c) one,
                        // divide each value on row r with the value at ai(c,c)
                        double f = ai(c, c);
                        for (int s = 1; s <= cols; s++) {
                            ai(r, s) /= f;
                            res(r, s) /= f;
                        }
                    }
                }
            }
        }
        return res;
    }
};

#endif	/* MATRIX_H */