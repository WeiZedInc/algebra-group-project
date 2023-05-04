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
    T koef;

public:
    Node();
    Node(T koef, size_t degree);
    ~Node() = default;

    size_t deg() const;
    T k() const;

    bool operator>(const Node<T> &p2) const;
    bool operator>=(const Node<T> &p2) const;
    bool operator<(const Node<T> &p2) const;
    bool operator<=(const Node<T> &p2) const;

    bool operator!=(const Node<T> &p2) const;
    Node<T> operator+(const Node<T> &p2) const;
    Node<T> operator-(const Node<T> &p2) const;
    void operator=(const Node<T> &p2);
    bool operator==(const Node<T> &p2) const;

    T evaluate() const { return fpow(koef, degree); };
};
#endif

#ifndef POLYNOMIAL
#define POLYNOMIAL
template <typename T>
class Polynomial
{
private:
    std::list<Node<modNum<T>>> poly;
    size_t degree; // polynomial degree

public:
    Polynomial() = default;

    ~Polynomial() = default;

    Node<T> operator[](const size_t i); // use only when really necessary

    bool empty();
    typename std::list<Node<modNum<T>>>::const_iterator begin() const { return poly.begin(); };
    typename std::list<Node<modNum<T>>>::const_iterator end() const { return poly.end(); };

    void addNode(const Node<modNum<T>>);

    void removeNode(const Node<modNum<T>>); // by value
    void removeNode(const size_t);          // by degree

    size_t deg() const { return degree; };

    //////////////////////////////////////////////////////////////////////////////

    Polynomial<modNum<T>> operator+(const Polynomial<modNum<T>> &) const;
    Polynomial<modNum<T>> operator-(const Polynomial<modNum<T>> &) const;
    Polynomial<modNum<T>> operator*(const Polynomial<modNum<T>> &) const;

    //////////////////////////////////////////////////////////////////////////////

    Polynomial<modNum<T>> der() const; // deriveative
    modNum<modNum<T>> evaluate() const;

    //////////////////////////////////////////////////////////////////////////////

    std::pair<Polynomial<modNum<T>>, Polynomial<modNum<T>>> operator/(const Polynomial<T> &) const;

    Polynomial<modNum<T>> gcd(const Polynomial<modNum<T>> &) const;

    //////////////////////////////////////////////////////////////////////////////

    static Polynomial<modNum<T>> getPolynomialByOrder(size_t);
};
#endif

#include "source/node.tcc"
#include "source/poly-basic.tcc"
