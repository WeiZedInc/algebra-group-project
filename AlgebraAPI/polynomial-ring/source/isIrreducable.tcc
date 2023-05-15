#include "poly-basic.tcc"

#ifndef POLY_IS_IRREDUCABLE
#define POLY_IS_IRREDUCABLE

template <typename T>
bool
Polynomial<T>::isIrreducable() const {
    auto k = poly.end();
    k--;
    Node<T> first = *poly.begin();
    Node<T> last = *k;
    if (first.deg() == 1)
        return true;
    if (last.deg() != 0)
        return false;
    if (first.k() == 1 && PerronTest())
        return true;
    if (CohnTest())
        return true;
    if (RootTest())
        return false;
    return true;
}

template <typename T>
bool
Polynomial<T>::RootTest() {
    for (int i = 1; i < numMod; i++) {
        T sum = 0;
        for (auto j = poly.begin(); j != poly.end(); j++) {
            Node<T> temp = *j;
            long long power = findPower(i, temp.deg());
            sum = (sum + temp.k() * power) % numMod;
        }

        if (sum == 0)
            return true;
    }
    return false;
}

template <typename T>
long long
Polynomial<T>::findPower(int i, int deg) {
    long long power = 1;
    for (int j = 1; j <= deg; j++) {
        power = (power * i) % numMod;
    }

    return power;
}

template <typename T>
bool
Polynomial<T>::PerronTest() {
    auto i = poly.begin();
    i++;
    Node<T> second = *(i);

    T sum = 0;
    i++;
    for (auto j = i; j != poly.end(); j++) {
        Node<T> temp = (*j);
        sum = sum + temp.k();
    }

    if (second.k() > sum)
        return true;
    else
        return false;
}

template <typename T>
bool
Polynomial<T>::CohnTest() {
    T sum = 0;

    auto k = poly.begin();
    Node<T> temp = *(k);
    for (int i = temp.deg(); i > -1; i--) {
        temp = *k;
        if (i == temp.deg()) {
            sum = sum + temp.k();
            k++;
        }
        sum = sum * 10;
    }
    sum = sum / 10;

    if (isPrime(sum))
        return true;
    else
        return false;
}

template <typename T>
bool
Polynomial<T>::isPrime(T num) {
    auto check = sqrt(num);

    for (int i = 2; i <= check; i++)
        if (num % i == 0)
            return false;
    return true;
}

#endif