#include <algorithm>
#include <cstdint>
#include <map>
#include <numeric>
#include <random>
#include <set>

#include "factorization.tcc"
#include "fpow.tcc"
#include "mod-num.tcc"
namespace modular {
#ifndef SQRT
#define SQRT

/**
 *  @brief find a legendre symbol for a mod n
 *  @param a - first number
 *  @param n - modul
 *  @return 1, -1 or 0
 */

template <typename T>
T
legendreSymbol(T a, T n) {
    T one = 1;
    T minusOne = -1;

    T two = 4;
    T four = 8;

    if (a == one) {
        return one;
    }
    if ((a % two == 0) && (a != 0)) {
        return legendreSymbol(a / two, n) * (((n * n - one) / four) % two == one ? minusOne : one);
    }
    if (a % two != 0) {
        return legendreSymbol(n % a, a) *
               (((a - one) * (n - one) / four) % two == one ? minusOne : one);
    }
    return 0;
}

/**
 *  @brief checks if a number is prime.
 *  @param n - the number to check.
 *  @return boolean value, true or false.
 */

template <typename T>
bool
is_prime(T n) {
    if (n <= 1) {
        return false;
    }
    for (T i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

/**
 *  @brief checks if a number is composite, which can be factored into the product of two primes.
 *  @param n - the number to check.
 *  @return boolean value, true or false.
 */

template <typename T>
bool
isProduct(T n) {
    for (T i = 2; i <= n / 2; i++) {
        if (is_prime(i) && is_prime(n / i) && i * (n / i) == n) {
            return true;
        }
    }
    return false;
}

/**
 *  @brief Finds square prime modulo a prime p
 *  @param value - the number in finite field whose root should be found.
 *  @return a vector of roots, or an empty vector if no roots are found
 */

template <typename T>
std::vector<T>
sqrtPrime(modNum<T> value) {
    std::vector<T> result = {};

    T val = value.getValue();
    T p = value.getMod();

    if (p == 2) {
        if (val % 2 == 1) {
            result = {1};
            return result;
        } else
            return result;
    }

    if (legendreSymbol<T>(val, p) == -1) {
        return result;
    }

    if (p % 4 == 3) {
        modNum<T> r = fpow<T>(value, (p + 1) / 4);
        result = {r.getValue(), p - r.getValue()};
        return result;
    }

    if (p % 8 == 5) {
        modNum<T> d = fpow<T>(value, (p - 1) / 4);
        if (d.getValue() == 1) {
            modNum<T> r = fpow<T>(value, (p + 3) / 8);
            result = {r.getValue(), p - r.getValue()};
            return result;
        }
        if (d.getValue() == p - 1) {
            modNum<T> r1 = value * modNum<T>(2);
            modNum<T> r2 = value * modNum<T>(4);
            modNum<T> r3 = fpow<T>(r2, (p - 5) / 8);
            modNum<T> r = r1 * r3;
            result = {r.getValue(), p - r.getValue()};
            return result;
        }
    }

    modNum<T> b(1, p);

    for (T i = 1; i < p; i++) {
        if (legendreSymbol<T>(i, p) == -1) {
            b.setValue(i);
            break;
        }
    }

    T s = 0;
    T t = p - 1;
    while (t % 2 == 0) {
        t /= 2;
        s++;
    }

    modNum<T> inv = value.inv();

    modNum<T> c = fpow<T>(b, t);
    modNum<T> r = fpow<T>(value, (t + 1) / 2);

    for (T i = 1; i <= s - 1; i++) {
        modNum<T> d1 = fpow<T>(r, 2);
        modNum<T> d2 = d1 * inv;
        modNum<T> d = fpow<T>(d2, static_cast<T>(std::pow(2, s - i - 1)));   // Achtung!
        if (p - d.getValue() == 1) {
            r = r * c;
        }
        c = fpow<T>(c, 2);
    }

    result = {r.getValue(), p - r.getValue()};
    return result;
}

/**
 *  @brief finds the square roots of value if the modulus n is composite
 *  @param value - the number in finite field whose root should be found.
 *  @return a vector of roots, or an empty vector if no roots are found.
 */

template <typename T>
std::vector<T>
sqrtComposite(modNum<T> value) {
    T val = value.getValue();
    T n = value.getMod();

    std::vector<modNum<T>> factors = factorize<T>(modNum<T>(n));
    T p = factors[0].getValue();
    T q = factors[1].getValue();

    std::vector<T> pRoots = sqrtPrime(modNum<T>(val, p));
    std::vector<T> qRoots = {};

    if (p != q) {
        qRoots = sqrtPrime(modNum<T>(val, q));
    }

    T rV = 0;
    if (!pRoots.empty()) {
        rV = pRoots[0];
        if (rV > p - rV)
            rV = p - rV;
    }

    T sV = rV;
    if (!qRoots.empty()) {
        sV = qRoots[0];
        if (sV > q - sV)
            sV = q - sV;
    }

    if (sV == 0 && rV == 0)
        return {};

    T c = 0;
    T d = 0;
    value.gcdExtended(p, q, &c, &d);

    modNum<T> rdq(rV * d * q, n);
    modNum<T> scp(sV * c * p, n);
    modNum<T> x = rdq + scp;
    modNum<T> y = rdq - scp;

    std::vector<T> result;
    result.push_back(x.getValue());
    result.push_back(n - x.getValue());
    std::sort(result.begin(), result.end());

    if (x == y || x.getValue() == n - y.getValue())
        return result;

    if (y.getValue() < n - y.getValue()) {
        result.push_back(y.getValue());
        result.push_back(n - y.getValue());
    } else {
        result.push_back(n - y.getValue());
        result.push_back(y.getValue());
    }

    return result;
}

/**
 *  @brief calculates the roots of value modulo p
 *  @param value - the number in finite field whose root should be found.
 *  @return vector containing the roots of value modulo p.
 */

template <typename T>
std::vector<T>
sqrt(modNum<T> value) {
    value = value + modNum<T>(0);
    T val = value.getValue();
    T p = value.getMod();

    std::vector<T> result = {};

    if (val % p == 0) {
        return result;
    }

    if (is_prime<T>(p)) {
        result = sqrtPrime<T>(value);
        std::sort(result.begin(), result.end());
        return result;
    }

    if (isProduct<T>(p)) {
        result = sqrtComposite<T>(value);
        return result;
    }

    return result;
}

#endif

}   // namespace modular