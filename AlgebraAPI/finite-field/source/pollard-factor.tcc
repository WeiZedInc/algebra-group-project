#include <iostream>
#include <vector>
#include "mod-num.tcc"
#include "fpow.tcc"

#ifndef POLLARD_FACTORIZATION
#define POLLARD_FACTORIZATION

/**
*  @brief Calculating GCD
*  @param a first number
*  @param b second number
*
*
*  @return GCD
*/
template <typename T1>
T1 gcd(T1 a, T1 b) 
{
    return b == 0 ? a : gcd(b, a % b);
}

/**
*  @brief Checks if the number is prime or not
*  @param a first number
*
*
*  @return true or false
*/
template <typename T1>
bool isPrime(T1 a) 
{
    for (int i = 2; i <= sqrt(a); ++i) 
        if (a % i == 0) 
            return false;
    return true;
}

/**
*  @brief Calculating a polynomial in x computed modulo mod
*  @param x value
*  @param mod modulo
*
*
*  @return polynomial in x computed modulo mod 
*/
template <typename T1>
T1 F(T1 x, T1 mod) 
{
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
T1 pollardRhO(T1 n)  
{
    if (n % 2 == 0)
        return 2;

    T1 x = 2;
    T1 y = 2;
    T1 d = 1;

    while(d == 1)
    {
        x = F(x,n);    
        y = F(F(y,n),n);
        d = gcd(abs(x - y), n);
    }
    return d;
}

/**
*  @brief Factorization using Pollard's rho algorithm
*  @param value number
*
*
*  @return vector of factors
*/
template <typename T1>
std::vector<modNum<T1>> factorize(modNum<T1> value)
{
    if (value < 1)
        throw std::invalid_argument(std::to_string(value.getValue()) + " is less than 1");
    else if (value == 1)
        return std::vector<modNum<T1>>{};
    else if (isPrime(value.getValue()))
        return std::vector<modNum<T1>>{value};

    std::vector<modNum<T1>> factors;

    T1 divisor = pollardRhO(value.getValue());
    if (isPrime(divisor)) 
        factors.push_back(modNum<T1>(divisor));
    else 
    {
        std::vector<modNum<T1>> tmp = factorize(modNum<T1>(divisor));
        factors.insert(factors.end(), tmp.begin(), tmp.end());
    }

    std::vector<modNum<T1>> tmp = factorize(modNum<T1>(value.getValue() / divisor));
    factors.insert(factors.end(), tmp.begin(), tmp.end());

    return factors;
}

#endif   
