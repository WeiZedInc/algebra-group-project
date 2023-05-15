#include <cmath>

#include "../../finite-field/mod-math.h"
#include "../../polynomial-ring/poly-ring-math.h"

using namespace modular;

#ifndef POLY_FIELD
#define POLY_FIELD

template <typename T>
bool
isPrimeSimpleFunction(T num) {
    T check = sqrt(num);

    for (int i = 2; i <= check; i++)
        if (num % i == 0)
            return false;
    return true;
}

template <typename T>
typename std::vector<T> nodes;
template <typename T>

class PolynomialField {
   protected:
    T numMod;

    Polynomial<T> value;
    Polynomial<T> MOD;

   public:
    PolynomialField(T mod, Polynomial<T> polyMod) {
        if (isPrimeSimpleFunction(mod)) {
            this->numMod = mod;
            this->MOD = polyMod;
        } else
            throw std::invalid_argument("Mod should be prime");
    }

    PolynomialField() = default;

    PolynomialField<T> operator+(const PolynomialField<T> &) const;
    PolynomialField<T> operator-(const PolynomialField<T> &) const;
    PolynomialField<T> operator*(const PolynomialField<T> &) const;
    PolynomialField<T> operator*(T num) const;

    bool operator==(const PolynomialField<T> &) const;
    PolynomialField<T> pow(T k);

    void addNode(const T num, size_t deg);

    static std::vector<PolynomialField<T>> findKIrreducible(size_t k);

    bool isIrreducible();

    void normalize();

    PolynomialField<T> inv();

    size_t getOrder();

    bool isGenerator();
};

#endif

#ifndef POLY_FIELD_BASICS_IMPLEMENTATION
#define POLY_FIELD_BASICS_IMPLEMENTATION

template <typename T>
void
PolynomialField<T>::addNode(const T num, size_t deg) {
    Polynomial<T>::addNode(num, deg % polyMod);
}

template <typename T>
PolynomialField<T>
PolynomialField<T>::operator+(const PolynomialField<T> &other) const {
    return (this->value + other->value) % MOD;
}

template <typename T>
PolynomialField<T>
PolynomialField<T>::operator-(const PolynomialField<T> &other) const {
    return (this->value - other->value) % MOD;
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
    res = (this->value + other->value) % MOD;
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