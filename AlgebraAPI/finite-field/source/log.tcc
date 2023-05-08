#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "fpow.tcc"
#include "mod-num.tcc"
namespace modular {
#ifndef LOG_H
#define LOG_H

template <class numT>
bool
isGenrator2(modNum<numT>, std::string) {
    return true;
}
template <class numT>
struct customHash {
   private:
    std::hash<numT> hasher;

   public:
    size_t operator()(const modNum<numT> &number) const { return hasher(number.getValue()); }
};
template <class numT>
size_t
log(modNum<numT> value, modNum<numT> base) {
    if (!isGenrator2(base, "+"))
        throw std::invalid_argument("Base of a logarithm must be a group Generator");

    numT m = static_cast<numT>(std::sqrt(base.getMod())) + 1;

    std::unordered_map<modNum<numT>, size_t, customHash<numT>> table;

    modNum<numT> basePowed(1, base.getMod());
    for (numT i = 0; i < m; ++i) {
        table.insert({basePowed, i});
        basePowed = base * basePowed;
    }

    modNum<numT> alphaInversed = fpow(base.inv(), m);
    modNum<numT> gamma = value;

    for (numT i = 0; i < m; ++i) {
        if (table.find(gamma) != table.end()) {
            return i * m + table[gamma];
        }
        gamma = gamma * alphaInversed;
    }

    throw std::invalid_argument("Unexpected behaviour");
}
#endif

}   // namespace modular