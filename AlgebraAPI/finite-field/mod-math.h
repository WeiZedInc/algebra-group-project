#include "mod-int.h"
#include <vector>

namespace modular
{
    template <typename _T>
    modInt<_T> log(modInt<_T> __value, modInt<_T> __base); // discrete logarithm

    template <typename _T>
    modInt<_T> pow(modInt<_T> __value, modInt<_T> __base); // regular pow

    template <typename _T>
    modInt<_T> fpow(modInt<_T> __value, modInt<_T> __base); // fast pow

    template <typename _T>
    std::vector<_T> factorize(modInt<_T> __value); // number factorization using Polard algorithm

    template <typename _T>
    std::vector<_T> naiveFactorize(modInt<_T> __value); // naive number factorization

    template <typename _T>
    modInt<_T> fpow(modInt<_T> __value, modInt<_T> __base);

    template <typename _T>
    modInt<_T> fpow(modInt<_T> __value, modInt<_T> __base);
}