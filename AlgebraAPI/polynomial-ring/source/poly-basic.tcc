#pragma once
#include <list>
#include <iostream>
#include "node.tcc"

#ifndef POLYNOMIAL
#define POLYNOMIAL
template <typename T>
class Polynomial
{
private:
    std::list<Node<T>> poly;

public:
    Polynomial() = default;
    ~Polynomial() = default;

    void addNode(Node<T>);

    Node<T> operator[](const int i);
};

#endif

template <typename T>
Node<T> Polynomial<T>::operator[](const int i)
{

    if (i < 0 || i >= poly.size())
        throw std::out_of_range("Index out of range");

    int j = 0;
    for (auto it = poly.begin(); it != poly.end(); ++it)
    {
        if (i == j)
            return *it;
        j++;
    }
}

template <typename T>
void Polynomial<T>::addNode(Node<T> p)
{
    poly.push_back(p);
}

template <typename T>
std::ostream &operator<<(std::ostream &os, Node<T> &p)
{
    return os << '{' << p.power() << ", " << p.koeficient() << '}';
}