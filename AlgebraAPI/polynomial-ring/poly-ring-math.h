#pragma once
#include <list>
#include <iostream>
#include <vector>
#include "../finite-field/mod-math.h"

using namespace modular;

#ifndef POLY_NODE_H
#define POLY_NODE_H
template <typename T>
class Node
{
private:
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

#ifndef POLYNOMIAL
#define POLYNOMIAL
template <typename T>
class Polynomial
{
private:
    std::list<Node<T>> poly;
    size_t degree = 0;
    T numMod = 0;

public:
    Polynomial(T mod) : numMod(mod){};
    Polynomial(std::vector<std::pair<T, size_t>>, T);
    Polynomial(std::pair<T, size_t> *arr, size_t n, T);

    ~Polynomial() = default;

    Node<T> operator[](const size_t i); // use only when really necessary

    bool empty();
    typename std::list<Node<T>>::const_iterator begin() const { return poly.begin(); };
    typename std::list<Node<T>>::const_iterator end() const { return poly.end(); };

    void addNode(const Node<T>);
    void addNode(const T, size_t);

    void removeNode(const Node<T>); // by value
    void removeNode(const size_t);  // by degree

    size_t getDegree() const { return degree; };
    T getNumMod() const { return numMod; }

    void print() const;

    //////////////////////////////////////////////////////////////////////////////

    Polynomial<T> operator+(const Polynomial<T> &) const;
    Polynomial<T> operator-(const Polynomial<T> &) const;
    Polynomial<T> operator*(const Polynomial<T> &) const;

    //////////////////////////////////////////////////////////////////////////////

    Polynomial<T> der() const; // deriveative
    modNum<T> evaluate(const T) const;
    modNum<T> evaluate(const modNum<T>) const;

    //////////////////////////////////////////////////////////////////////////////

    std::pair<Polynomial<T>, Polynomial<T>> operator/(const Polynomial<T> &) const;

    Polynomial<T> gcd(const Polynomial<T> &) const;

    //////////////////////////////////////////////////////////////////////////////

    static Polynomial<T> getPolynomialByOrder(size_t);
};
#endif

#include "source/node.tcc"
#include "source/poly-basic.tcc"
