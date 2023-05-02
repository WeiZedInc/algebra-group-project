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

template <typename T>
Node<T> Polynomial<T>::operator[](const size_t i)
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
std::ostream &operator<<(std::ostream &os, Node<T> &p)
{
    return os << '{' << p.power() << ", " << p.koeficient() << '}';
}
