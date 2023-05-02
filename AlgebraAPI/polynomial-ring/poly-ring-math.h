#pragma once
#include <list>
#include <iostream>
#include <vector>
#include <../finite-field/mod-math.h>

#ifndef POLY_NODE
#define POLY_NODE

template <typename T>
class Node
{
private:
    size_t pow;
    T koef;

public:
    Node();
    Node(T koef, size_t pow);
    ~Node() = default;

    size_t pow();
    modNum<T> koef();

    bool operator>(const Node &p2);
    bool operator>=(const Node p2);
    bool operator<(const Node p2);
    bool operator<=(const Node p2);

    bool operator!=(const Node p2);
    Node operator+(const Node p2);
    Node operator-(const Node p2);
    void operator=(const Node &p2);

    modular::modNum<T> evaluate();
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
    T mod; // also a field

public:
    Polynomial() = default;
    ~Polynomial() = default;
    Node<T> operator[](const size_t i);

    bool empty();

    void addNode(Node<T>);
    void removeNode(Node<T>); // by value
    void removeNode(size_t);  // by degree

    // getters
    size_t deg();
    //////////////////////////////////////////////////////////////////////////////
    Polynomial<T> operator+(const &Polynomial<T>);
    Polynomial<T> operator-(const &Polynomial<T>);
    Polynomial<T> operator*(const &Polynomial<T>);

    //////////////////////////////////////////////////////////////////////////////

    std::pair<Polynomial<T>, Polynomial<T>> operator/(const &Polynomial<T>);
    std::pair<Polynomial<T>> operator/(const &Polynomial<T>);
    Polynomial<T> gcd(const &Polynomial<T>);

    //////////////////////////////////////////////////////////////////////////////

    Polynomial<T> der();
    modular::modNum<T> evaluate();
    //////////////////////////////////////////////////////////////////////////////

    static Polynomial getPolynomialByOrder(size_t);
};
#endif
