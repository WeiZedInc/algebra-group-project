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
class PolynomialField : public Polynomial<T> {
   protected:
    size_t polyMod;

   public:
    PolynomialField(T mod, T polymod) {
        if (isPrimeSimpleFunction(mod))
            this->numMod = mod;
        else
            throw std::invalid_argument("Mod should be prime");
        this->polyMod = polymod;
    }
    PolynomialField() = default;
    PolynomialField<T> operator+(const PolynomialField<T> &) const;
    PolynomialField<T> operator-(const PolynomialField<T> &) const;
    PolynomialField<T> operator*(const PolynomialField<T> &) const;
    PolynomialField<T> operator*(T num) const;
    bool operator==(const PolynomialField<T> &) const;
    PolynomialField<T> pow(size_t k);
    void addNode(const T num, size_t deg);

    static std::vector<PolynomialField<T>> findKIrreducible(size_t k);

    bool isIrreducible();

    void normalize();

    PolynomialField<T> inv();

    size_t getOrder();

    bool isGenerator();
};

template <typename T>
void
PolynomialField<T>::addNode(const T num, size_t deg) {
    Polynomial<T>::addNode(num, deg % polyMod);
}

template <typename T>
PolynomialField<T>
PolynomialField<T>::operator+(const PolynomialField<T> &other) const {
    if (other.polyMod != this->polyMod) {
        throw std::invalid_argument("Polynomial degree modulas are different");
    } else {
        PolynomialField<T> res(this->numMod, this->polyMod);
        res = this->Polynomial<T>::operator+(other);
        return res;
    }
}

template <typename T>
PolynomialField<T>
PolynomialField<T>::operator-(const PolynomialField<T> &other) const {
    if (other.polyMod != this->polyMod) {
        throw std::invalid_argument("Polynomial degree modulas are different");
    } else {
        PolynomialField<T> res(this->numMod, this->polyMod);
        res = this->Polynomial<T>::operator-(other);
        return res;
    }
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
    PolynomialField<T> res(this->numMod, this->polyMod);
    if (this->getNumMod() != other.getNumMod()) {
        throw std::invalid_argument("Can't add Polynomials with diferent modulas");
    }

    std::size_t s = this->poly.size() + other.poly.size() - 1;
    PolynomialField<T> result(this->numMod, this->polyMod);
    result.degree = s - 1;
    auto it = this->poly.begin();

    while (it != this->poly.end()) {
        auto io = other.poly.begin();
        while (io != other.poly.end()) {
            modNum<T> t1 = it->k();
            modNum<T> t2 = io->k();
            modNum<T> temp = t1 * t2;

            result.addNode(temp.getValue(), (it->deg() + io->deg() % this->polyMod));
            io++;
        }
        it++;
    }

    auto temp = result.poly.begin();
    while (temp != result.poly.end()) {
        if ((temp->k()).getValue() == 0)
            temp = result.poly.erase(temp);
        temp++;
    }
    return result;
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
PolynomialField<T>::pow(size_t k) {
    if (k == 0) {
        PolynomialField<T> p(this->numMod, this->polyMod);
        p.addNode(1, 0);
        return p;
    } else if (k % 2 == 0) {
        PolynomialField<T> res(this->numMod, this->polyMod);
        res = pow(k / 2);
        return res * res;
    } else {
        PolynomialField<T> res(this->numMod, this->polyMod);
        res = pow(k - 1);
        return res * (*this);
    }
}

#endif