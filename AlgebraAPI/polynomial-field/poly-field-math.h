#include "../finite-field/mod-math.h"
#include "../polynomial-ring/poly-ring-math.h"

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

#endif