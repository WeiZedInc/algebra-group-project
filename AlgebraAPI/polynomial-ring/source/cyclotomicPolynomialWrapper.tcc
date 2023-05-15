#include "../poly-ring-math.h"
using namespace modular;

template <typename T>
void
Polynomial<T>::fromCyclotomic(T order, T mod) {
    this->numMod = mod;
    return Polynomial<T>::getCyclotomicPolynomial(order, mod);
}