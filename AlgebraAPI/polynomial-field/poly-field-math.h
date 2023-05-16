#ifndef POLY_FIELD
#define POLY_FIELD

#include "../polynomial-ring/poly-ring-math.h"

using namespace modular;

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

#include "source//poly-field-basic.tcc"

#endif