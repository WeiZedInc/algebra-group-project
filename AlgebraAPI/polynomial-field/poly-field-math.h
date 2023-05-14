#include "../finite-field/mod-math.h"
#include "../polynomial-ring/poly-ring-math.h"

using namespace modular;

#ifndef POLY_FIELD
#define POLY_FIELD

template <typename T>
typename std::vector<T> nodes;

template <typename T>
class PolynomialField : public Polynomial<modNum<T>> {
   protected:
    size_t polyMod;
    size_t order = 0;   // degree of polynom

   public:
    PolynomialField() = default;
    PolynomialField(T mod, T polymod);
    PolynomialField<T> operator+(const PolynomialField<T> &) const;
    PolynomialField<T> operator-(const PolynomialField<T> &) const;
    PolynomialField<T> operator*(const PolynomialField<T> &) const;
    PolynomialField<T> operator*(T num) const;
    bool operator==(const PolynomialField<T> &) const;
    PolynomialField<T> pow(size_t k);
    void addNode(const T num, size_t deg) const;

    static std::vector<PolynomialField<T>> findKIrreducible(size_t k);

    bool isIrreducible();

    void normalize();

    PolynomialField<T> inv();

    size_t getOrder();

    bool isGenerator();
};

#endif