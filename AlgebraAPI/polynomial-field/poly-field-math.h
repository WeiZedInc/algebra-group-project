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
    T mod;
    size_t order = 0;

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