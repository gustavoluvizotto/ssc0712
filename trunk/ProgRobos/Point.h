#ifndef POINT_H
#define	POINT_H

#include <cmath>
#include <iostream>

// Eleva ao quadrado
#ifndef POW
#define POW(x)  ((x) * (x))
#endif

template <class _T3>
class Point {
private:
    _T3 x, y;

public:

    Point() {
        x = y = 0;
    }

    /**
     * Construtor a partir de valores fornecidos de x e y 
     * @param X x fornecido
     * @param Y y fornecido
     */
    Point(const _T3 xval, const _T3 yval) {
        Set(xval, yval);
    }

    /**
     * Construtor a partir de um Ponto existente fornecido
     * @param orig Ponto existente fornecido
     */
    Point(const Point<_T3>& orig) {
        Set(orig.x, orig.y);
    }

    virtual ~Point() {
    }

    _T3 GetX() const {
        return x;
    }

    void SetX(_T3 val) {
        x = val;
    }

    _T3 GetY() const {
        return y;
    }

    void SetY(_T3 val) {
        y = val;
    }

    void Set(const _T3 xval, const _T3 yval) {
        x = (_T3) xval;
        y = (_T3) yval;
    }

    /**
     * Distância entre 'this' e o ponto P
     * @param P ponto que se deseja medir a distância
     * @return a distância entre 'this'e o ponto P fornecido
     */
    double GetDistance(Point<_T3>& P) const {
        return sqrt(POW(x - P.x) + POW(y - P.y));
    }

    /**
     * Distância entre 2 pontos
     * @param P1 ponto 1
     * @param P2 ponto 2
     * @return distância entre os pontos 1 e 2
     */
    static double GetDistance(Point<_T3>& P1, Point<_T3>& P2) {
        return sqrt(POW(P2.x - P1.x) + POW(P2.y - P1.y));
    }

    /**
     * Imprime os valores x e y do ponto
     */
    void Print() {
        std::cout << "[" << x << ", " << y << "]" << std::endl;
    }

    /**
     * Clona o ponto fornecido como parâmetro, e retorna esse ponto
     * @param P ponto a ser clonado
     * @return um ponto novo, clonado a partir do ponto fornecido como parâmetro
     */
    Point<_T3>& operator=(const Point<_T3>& P) {
        x = P.x;
        y = P.y;
        return *this;
    }

    /**
     * Soma P a 'this'
     * @param P ponto a ser somado a este (this)
     * @return o mesmo ponto (this), porém acrescido de P
     */
    Point<_T3>& operator+=(const Point<_T3>& P) {
        *this = *this +P;
        return *this;
    }

    /**
     * Retorna um novo ponto obtido da soma P1 + P2
     */
    friend Point<_T3> operator+(const Point<_T3>& P1, const Point<_T3>& P2) {
        Point<_T3> res(P1.x + P2.x, P1.y + P2.y);
        return res;
    }

    /**
     * Divide 'this' por val.
     * @param val valor que divide 'this'
     * @return o mesmo ponto (this), porém dividido por val
     */
    Point<_T3>& operator/=(const double val) {
        *this = *this / val;
        return *this;
    }

    /**
     * Retorna um novo ponto obtido da divisão P / val.
     */
    friend Point<_T3> operator/(const Point<_T3>& P, const double val) {
        Point<_T3> res(P.x / val, P.y / val);
        return res;
    }

    /**
     * Subtrai P de 'this'
     * @param P ponto a ser subtraído de 'this'
     * @return o mesmo ponto (this), porém subtraído de P
     */
    Point<_T3>& operator-=(const Point<_T3>& P) {
        *this = *this -P;
        return *this;
    }

    /** 
     * Retorna um novo ponto obtido da subtração P1 - P2
     */
    friend Point<_T3> operator-(const Point<_T3>& P1, const Point<_T3>& P2) {
        Point<_T3> res(P1.x - P2.x, P1.y - P2.y);
        return res;
    }

    /**
     * Operador 'menos unário' = 'negativo'. Retorna um novo ponto, simétrico a P.
     */
    friend Point<_T3> operator-(const Point<_T3>& P) {
        Point<_T3> res(-P.x, -P.y);
        return res;
    }

    /**
     * Multiplica P com 'this'
     * @param P ponto a ser multiplicado por 'this'
     * @return o mesmo ponto (this), porém multiplicado por P
     */
    Point<_T3>& operator*=(const Point<_T3>& P) {
        *this = *this * P;
        return *this;
    }

    /** 
     * Retorna um novo ponto obtido da multiplicação P1 * P2, ordenada a ordenada
     */
    friend Point<_T3> operator*(const Point<_T3>& P1, const Point<_T3>& P2) {
        Point<_T3> res(P1.x * P2.x, P1.y * P2.y);
        return res;
    }

    /** 
     * Retorna um novo ponto obtido da multiplicação P * val
     */
    friend Point<_T3> operator*(const Point<_T3>& P, const double val) {
        Point<_T3> res(P.x * val, P.y * val);
        return res;
    }

    /** 
     * Retorna um novo ponto obtido da multiplicação val * P
     */
    friend Point<_T3> operator*(const double val, const Point<_T3>& P) {
        return P * val;
    }

    /**
     * Operador comparação. Retorna true se os pontos são iguais. false caso contrário.
     */
    bool operator==(const Point<_T3>& P) const {
        return (x == P.x && y == P.y);
    }
};

#endif	/* POINT_H */