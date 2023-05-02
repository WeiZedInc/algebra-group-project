#pragma once
#include <list>
#include <iostream>
#include <vector>

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

    T evaluate() const;
};
#endif

#ifndef POLYNOMIAL
#define POLYNOMIAL
template <typename T>
class Polynomial
{
private:
    std::list<Node<T>> poly;
    size_t degree;

public:
    Polynomial() = default;

    ~Polynomial() = default;

    Node<T> operator[](const size_t i); // use only when really necessary

    bool empty();
    typename std::list<Node<T>>::const_iterator begin() const;
    typename std::list<Node<T>>::const_iterator end() const;

    void addNode(const Node<T>);

    void removeNode(const Node<T>); // by value
    void removeNode(const size_t);  // by degree

    size_t deg() const;

    //////////////////////////////////////////////////////////////////////////////

    Polynomial<T> operator+(const Polynomial<T> &) const;
    Polynomial<T> operator-(const Polynomial<T> &) const;
    Polynomial<T> operator*(const Polynomial<T> &) const;

    //////////////////////////////////////////////////////////////////////////////

    Polynomial<T> der() const; // deriveative
    T evaluate() const;

    //////////////////////////////////////////////////////////////////////////////

    std::pair<Polynomial<T>, Polynomial<T>> operator/(const Polynomial<T> &) const;

    Polynomial<T> gcd(const Polynomial<T> &) const;

    //////////////////////////////////////////////////////////////////////////////

    static Polynomial<T> getPolynomialByOrder(size_t);
};
#endif

#include "source/node.tcc"
#include "source/poly-basic.tcc"
