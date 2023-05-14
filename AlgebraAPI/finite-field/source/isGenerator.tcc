#include <numeric>
#include <utility>

#include "factorization.tcc"
#include "mod-num.tcc"

namespace modular {
#ifndef IS_GENERATOR_TCC
#define IS_GENERATOR_TCC

template <typename T>
bool
isGenerator(modNum<T> a) {
    T t = a.getMod();
    modNum<T> b, one(static_cast<T>(1), a.getMod());

    vector<modNum<T>> factors = factorize(modNum(t - 1, t + 1));

    std::map<modNum<T>, size_t> factorsCombined;

    for (auto factor : factors) {
        factorsCombined[factor]++;
    }

    for (auto num : factorsCombined) {
        b = fpow(a, a.getMod() / num.first.getValue());
        if (b == one)
            return false;
    }
    return true;
}

#endif

}   // namespace modular