#include <cmath>
#include <map>
#include <vector>

#include "mod-num.tcc"

using namespace std;
namespace modular {

#ifndef EULER_CARMICAEL
#define EULER_CARMICAEL

template <typename T, typename floating = double>
floating
EulerFunction(T n) {
    if (n <= static_cast<T>(0))
        throw logic_error("Euler totient function is not defiend on non Natural values");

    floating res = n.get_d();   // suitable only when T is mpz_class
    floating one(1.0);

    for (T p = static_cast<T>(2); p * p <= n; p += static_cast<T>(1)) {
        if (n % p == static_cast<T>(0)) {
            while (n % p == static_cast<T>(0)) n /= p;
            res *= (one - (one / p.get_d()));
        }
    }

    if (n > static_cast<T>(1))
        res -= res / (n.get_d());
    return res;
}

template <typename T, typename floating = double>
modNum<T>
eulerFunction(modNum<T> num) {
    return modNum<T>(static_cast<T>(EulerFunction(num.getValue())), num.getMod());
}

template <typename T>
T
gcd(T a, T b) {
    if (b == static_cast<T>(0))
        return a;
    return gcd(b, a % b);
}

template <typename T>
modNum<T>
carmichaelFunction(modNum<T> num) {
    T n = num.getValue();
    if (n <= 0)
        throw logic_error("Carmichael function is not defiend on non Natural values");

    if (n == 1)
        return modNum<T>(static_cast<T>(1), num.getMod());

    std::vector<modNum<T>> factors = factorize(num);

    std::map<modNum<T>, T> tmp;
    for (auto num : factors) {
        tmp[num]++;
    }

    std::vector<T> factorsCombined;

    for (auto ths : tmp) {
        factorsCombined.push_back(fpow(ths.first, ths.second).getValue());
    }

    if (n != 1)
        factorsCombined.push_back(n - static_cast<T>(1));

    T res = 1;

    for (auto i : factorsCombined) {
        res = res * (i / gcd(res, i));
    }

    return modNum<T>(res, num.getMod());
}

#endif

}   // namespace modular
