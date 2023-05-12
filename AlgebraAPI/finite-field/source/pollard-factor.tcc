#include <cmath>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "mod-num.tcc"

using namespace std;

#ifndef POLLARD_FACTORIZATION
#define POLLARD_FACTORIZATION

/**
 *  @brief Calculating GCD
 *  @param a first number
 *  @param b second number
 *  @return GCD
 */
template <typename T1, typename T2>
T1
gcd(T1 a, T2 b) {
    return b == 0 ? a : gcd(b, a % b);
}

/**
 *  @brief Checks if the number is prime or not
 *  @param a first number
 *  @return true or false
 */
template <typename T1>
bool
isPrimeSimple(T1 a) {
    for (int i = 2; i <= sqrt(a); ++i)
        if (a % i == 0)
            return false;
    return true;
}

/**
 *  @brief Calculating a polynomial in x computed modulo mod
 *  @param x value
 *  @param mod modulo
 *  @return polynomial in x computed modulo mod
 */
template <typename T1>
T1
F(T1 x, T1 mod) {
    T1 a = rand() % 10;
    return (x * x + (1 + 2 * a)) % mod;
}

/**
 *  @brief Pollard's rho algorithm
 *  @param n number
 *
 *
 *  @return factor
 */
template <typename T1>
T1
pollardRhO(T1 n) {
    if (n % 2 == 0)
        return 2;

    T1 x = 2;
    T1 y = 2;
    T1 d = 1;

    while (d == 1) {
        x = F(x, n);
        y = F(F(y, n), n);
        d = gcd(abs(x - y), n);
    }
    return d;
}

/**
 *  @brief Factorization using Pollard's rho algorithm
 *  @param value number
 *  @return vector of factors
 */
template <typename T1>
vector<modNum<T1>>
factorize(modNum<T1> value) {
    modNum<T1> one(1, value.getMod());
    if (value < one)
        throw invalid_argument(to_string(value.getValue()) + " is less than 1");
    else if (value == one)
        return vector<modNum<T1>>{};
    else if (isPrimeSimple(value.getValue()))
        return vector<modNum<T1>>{value};

    vector<modNum<T1>> factors;

    T1 divisor = pollardRhO(value.getValue());
    if (isPrimeSimple(divisor))
        factors.push_back(modNum<T1>(divisor, value.getMod()));
    else {
        vector<modNum<T1>> tmp = factorize(modNum<T1>(divisor, value.getMod()));
        factors.insert(factors.end(), tmp.begin(), tmp.end());
    }

    vector<modNum<T1>> tmp = factorize(modNum<T1>(value.getValue() / divisor, value.getMod()));
    factors.insert(factors.end(), tmp.begin(), tmp.end());

    return factors;
}

/**
 *  @brief Factorization using naive algorithm
 *  @param value number
 *  @return vector of factors
 */
template <typename T1>
vector<modNum<T1>>
naiveFactorize(modNum<T1> m) {
    modNum<T1> one(1, m.getMod());
    if (m < one)
        throw invalid_argument(to_string(m.getValue()) + " is less than 1");
    else if (m == one)
        return vector<modNum<T1>>{};

    vector<modNum<T1>> factors;

    T1 p = 2;
    while (p * p <= m.getValue()) {
        if (m.getValue() % p == 0) {
            m = modNum<T1>(m.getValue() / p, m.getMod());
            factors.push_back(modNum<T1>(p, m.getMod()));
        } else {
            p++;
        }
    }

    if (m > one)
        factors.push_back(m);

    return factors;
}

#endif
