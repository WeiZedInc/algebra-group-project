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
    Polynomial(std::vector<modNum<T>>);

    ~Polynomial() = default;

    Node<T> operator[](const size_t i); // use only when really necessary

    bool empty();
    typename std::list<Node<T>>::const_iterator begin() const;
    typename std::list<Node<T>>::const_iterator end() const;

    void addNode(const Node<T>);

    void removeNode(const Node<T>); // by value
    void removeNode(const size_t);  // by degree

    size_t deg() const;
    Polynomial<T> derivative();
    int evaluate(const T);

    void print();


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
Polynomial<T>::Polynomial(std::vector<modNum<T>>)
{
}

template <typename T>
std::ostream &operator<<(std::ostream &os, Node<T> &p)
{
    return os << '{' << p.power() << ", " << p.koeficient() << '}';
}

template <typename T>
Polynomial<T> Polynomial<T>::derivative() {
    Polynomial<T> returned_field;
    Node<T> current_newnode;
    T new_koef;
    T new_pow;

    for (auto it = poly.begin(); it != poly.end(); ++it)
    {
        new_koef = it->k() * it->deg();
        new_pow = it->deg() - 1;
        if (new_pow < 1) {
            new_koef = 0;
            new_pow = 0;
        }
        current_newnode = { new_pow, new_koef };
        returned_field.addNode(current_newnode);
    }

    return returned_field;
}

template <typename T>

//TODO: replace int with modular::modNum<T>
//modular::modNum<T> Field<T>::evaluate() {
int Polynomial<T>::evaluate(T x_value) {

    T sum = 0;
    T current_num = 0;

    for (auto it = poly.begin(); it != poly.end(); ++it)
    {
        if (it->deg() > 0) {
            current_num = std::pow(it->k() * x_value, it->deg());
        }
        else {
            current_num = it->k();
        }
        std::cout << current_num << std::endl;
        sum = sum + current_num;
    }

    return sum;
}

template <typename T>
void Polynomial<T>::print() {
    //boolean used for adding the plus sign
    bool first_number_checked = false;
    for (auto it = poly.begin(); it != poly.end(); ++it)
    {
        if (first_number_checked) {
            std::cout << " + ";
        }
        else {
            first_number_checked = true;
        }
        if (it->deg() > 0) {
            std::cout << it->k() << "x^" << it->deg();
        }
        else {
            std::cout << it->k();
        }
    }
}