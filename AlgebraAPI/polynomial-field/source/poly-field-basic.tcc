#ifndef POLY_FIELD_BASICS_IMPLEMENTATION
#define POLY_FIELD_BASICS_IMPLEMENTATION

#include <cmath>

#include "../poly-field-math.h"

using namespace modular;

template <typename T>
void
PolynomialField<T>::addNode(const T num, size_t deg) {
    Polynomial<T>::addNode(num, deg);
    this->value = this->value % MOD;
}

template <typename T>
PolynomialField<T>
PolynomialField<T>::operator+(const PolynomialField<T> &other) const {
    PolynomialField<T> res(numMod, MOD, (this->value + other->value) % MOD);
}

template <typename T>
PolynomialField<T>
PolynomialField<T>::operator-(const PolynomialField<T> &other) const {
    PolynomialField<T> res(numMod, MOD, (this->value - other->value) % MOD);
}

template <typename T>
PolynomialField<T>
PolynomialField<T>::operator*(T num) const {
    PolynomialField<T> res(this->numMod, this->polyMod);
    auto it = this->poly.begin();

    modNum<T> num1(num, this->numMod);

    while (it != this->poly.end()) {
        res.addNode((num1 * it->k()).getValue(), it->deg());
        it++;
    }
    return res;
}

template <typename T>
PolynomialField<T>
PolynomialField<T>::operator*(const PolynomialField<T> &other) const {
    PolynomialField<T> res(numMod, MOD, (this->value * other->value) % MOD);
}

template <typename T>
bool
PolynomialField<T>::operator==(const PolynomialField<T> &other) const {
    if (other.polyMod != this->polyMod) {
        return false;
    }
    return this->Polynomial<T>::operator==(other);
}

template <typename T>
PolynomialField<T>
PolynomialField<T>::pow(T power) {
    PolynomialField<T> valcp = this->value;

    PolynomialField<T> res(this->numMod, this->MOD);
    while (power) {
        if (power % 2 == 1)
            res = res * valcp;

        valcp = valcp * valcp;
        power /= 2;
    }

    return res;
}

#endif