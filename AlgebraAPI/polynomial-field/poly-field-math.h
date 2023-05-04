#include "../polynomial-ring/poly-ring-math.h"
#include "../finite-field/mod-math.h"

using namespace modular;

#ifndef POLY_FIELD
#define POLY_FIELD

template <typename T>
typename std::vector<T> nodes;

template <typename T>
class PolynomialField : public Polynomial<modNum<T>>
{
private:
    size_t polyMod;
    size_t order = 0; // degree of polynom

public:
    static std::vector<PolynomialField<T>> findKIrreducible(size_t k);

    bool isIrreducible();

    void normalize();

    PolynomialField<T> pow(size_t k);

    PolynomialField<T> inv();

    size_t getOrder();

    bool isGenerator();
};

#endif