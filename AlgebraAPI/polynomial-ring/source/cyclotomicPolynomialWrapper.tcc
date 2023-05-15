#include "poly-basic.tcc"

using namespace modular;

template <typename T>
void
Polynomial<T>::fromCyclotomic(T order, T mod) {
    this->numMod = mod;
}