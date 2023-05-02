#include <list>
#include <iostream>

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
    Node(T p1, T k1);
    ~Node() = default;

    size_t pow();
    T koef();

    bool operator>(const Node &p2);
    bool operator>=(const Node p2);
    bool operator<(const Node p2);
    bool operator<=(const Node p2);
    bool operator==(const Node p2);

    bool operator!=(const Node p2);
    Node operator+(const Node p2);
    Node operator-(const Node p2);
    void operator=(const Node &p2);
};
#endif

template <class T>
Node<T>::Node()
{
    pow = 0;
    koef = 0;
}
template <typename T>
Node<T>::Node(T p1, T k1)
{
    pow = p1;
    koef = k1;
}

template <typename T>
bool Node<T>::operator>(const Node &p2)
{
    return pow > p2.pow;
}

template <typename T>
bool Node<T>::operator>=(const Node p2)
{
    return pow >= p2.pow;
}

template <typename T>
bool Node<T>::operator<(const Node p2)
{
    return pow < p2.pow;
}

template <typename T>
bool Node<T>::operator<=(const Node p2)
{
    return pow <= p2.pow;
}

template <typename T>
bool Node<T>::operator==(const Node<T> p2)
{
    return pow == p2.pow;
}

template <typename T>
bool Node<T>::operator!=(const Node<T> p2)
{
    return pow != p2.pow;
}

template <typename T>
Node<T> Node<T>::operator+(const Node<T> p2)
{
    if (pow != p2.pow)
        throw std::logic_error("Can't add monominals with different powers");
    else
    {
        Node res(pow, koef + p2.koef);
        return res;
    }
}

template <typename T>
Node<T> Node<T>::operator-(const Node<T> p2)
{
    if (pow != p2.pow)
        throw std::logic_error("Can't substract monominals with different powers");
    else
    {
        Node res(pow, koef - p2.koef);
        return res;
    }
}

template <typename T>
void Node<T>::operator=(const Node<T> &p2)
{
    pow = p2.pow;
    koef = p2.koef;
}

template <typename T>
size_t Node<T>::pow()
{
    return pow;
}

template <typename T>
T Node<T>::koef()
{
    return koef;
}
