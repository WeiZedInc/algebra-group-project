#ifndef POLYNOMIAL
#define POLYNOMIAL

#include <iostream>
#include <list>
#include <vector>

#include "../finite-field/mod-math.h"

using namespace modular;

#ifndef POLY_NODE_H
#define POLY_NODE_H
template <typename T>
class Node {
   protected:
    size_t degree;
    modNum<T> koef;

   public:
    Node();
    Node(modNum<T> koef, size_t degree);
    ~Node() = default;

    size_t deg() const;
    modNum<T> k() const;

    bool operator>(const Node<T> &p2) const;
    bool operator>=(const Node<T> &p2) const;
    bool operator<(const Node<T> &p2) const;
    bool operator<=(const Node<T> &p2) const;

    bool operator!=(const Node<T> &p2) const;
    Node<T> operator+(const Node<T> &p2) const;
    Node<T> operator-(const Node<T> &p2) const;
    void operator=(const Node<T> &p2);
    bool operator==(const Node<T> &p2) const;

    modNum<T> evaluate(T) const;
};
#endif

template <typename T>
class Polynomial {
   protected:
    std::list<Node<T>> poly;
    size_t degree = 0;
    T numMod = 0;

    ///////////////////////Irreducable test///////////////////////////////////////////////////////
    bool PerronTest();
    bool CohnTest();
    bool RootTest();
    bool isPrime(
        T num);   // crutial part for some test; any ideas for better algorithm are welcomed
    long long findPower(int i, int deg);
    /////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////For polynomial long division//////////////////////////////////////////
    modNum<T> getCoeff(const size_t power);
    Polynomial<T> copy() const;
    Polynomial<T> shiftRight(int positions) const;
    /////////////////////////////////////////////////////////////////////////////////////////////

   public:
    Polynomial(T mod) {
        if (isPrime(mod))
            numMod = mod;
        else
            throw std::invalid_argument("Mod should be prime");
    };

    Polynomial() = default;
    Polynomial(std::vector<std::pair<T, size_t>>, T);
    Polynomial(std::pair<T, size_t> *arr, size_t n, T);

    ~Polynomial() = default;

    void fromCyclotomic(size_t order, T mod);

    Node<T> operator[](const size_t i);   // use only when really necessary

    bool empty();
    typename std::list<Node<T>>::const_iterator begin() const { return poly.begin(); };
    typename std::list<Node<T>>::const_iterator end() const { return poly.end(); };

    void addNode(const Node<T>);
    void addNode(const T, size_t);

    void removeNode(const Node<T>);   // by value
    void removeNode(const size_t);    // by degree

    size_t getDegree() const {
        if (poly.empty())
            return std::numeric_limits<int>::min();
        else
            return degree;
    };
    T getNumMod() const { return numMod; }

    std::vector<std::pair<T, size_t>> toPolyVector();

    void print() const;
    size_t size() const { return poly.size(); };

    //////////////////////////////////////////////////////////////////////////////

    Polynomial<T> operator+(const Polynomial<T> &) const;
    Polynomial<T> operator-(const Polynomial<T> &) const;
    Polynomial<T> operator*(const Polynomial<T> &) const;
    bool operator==(const Polynomial<T> &) const;

    //////////////////////////////////////////////////////////////////////////////

    Polynomial<T> der() const;   // deriveative
    modNum<T> evaluate(const T) const;
    modNum<T> evaluate(const modNum<T>) const;

    //////////////////////////////////////////////////////////////////////////////

    std::pair<Polynomial<T>, Polynomial<T>> divClassic(const Polynomial<T> &) const;
    std::pair<Polynomial<T>, Polynomial<T>> divClassic(const modNum<T> &) const;

    Polynomial<T> operator/(const Polynomial<T> &) const;
    Polynomial<T> operator%(const Polynomial<T> &) const;

    Polynomial<T> operator%(const modNum<T> &) const;
    Polynomial<T> operator/(const modNum<T> &) const;

    Polynomial<T> gcd(const Polynomial<T> &) const;

    //////////////////////////////////////////////////////////////////////////////

    static Polynomial<T> getPolynomialByOrder(size_t);

    bool isIrreducable() const;
};

#include "source/circular-polynomial.tcc"
#include "source/constructors.tcc"
#include "source/divAndGcd.tcc"
#include "source/isIrreducable.tcc"
#include "source/node.tcc"
#include "source/poly-basic.tcc"

#endif