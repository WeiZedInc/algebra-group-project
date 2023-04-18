#include <vector>
#include <string>

namespace modular
{
    template <typename T1, typename T2, typename T3, typename T4>
    T1 add(T2 value1, T3 value2, T4 MOD); // addition

    template <typename T1, typename T2, typename T3, typename T4>
    T1 subs(T2 value1, T3 value2, T4 MOD); // substruction

    template <typename T1, typename T2, typename T3, typename T4>
    T1 mult(T2 value1, T3 value2, T4 MOD); // multyplication

    ////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T1, typename T2, typename T3, typename T4>
    T1 div(T2 value1, T3 value2, T4 MOD); // division
    template <typename T1, typename T2, typename T3>
    T1 inv(T2 value1, T3 MOD); // inverse element

    /////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T1, typename T2, typename T3, typename T4>
    T1 pow(T2 value, T3 base, T4 MOD); // regular pow
    template <typename T1, typename T2, typename T3, typename T4>
    T1 fpow(T2 value, T3 base, T4 MOD); // fast pow

    //////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T1, typename T2, typename T3>
    std::vector<T1> factorize(T2 value, T3 MOD); // number factorization using Polard algorithm
    template <typename T1, typename T2, typename T3>
    std::vector<T1> naiveFactorize(T2 value, T3 MOD); // naive number factorization

    //////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T1, typename T2, typename T3, typename T4>
    T1 log(T2 value, T3 base, T4 MOD); // discrete logarithm

    //////////////////////////////////////////////////////////////////////////////////////////////

    // needs clarifications
    template <typename T1, typename T2>
    bool isGenrator(T1 value, std::string operation, T2 MOD); // is element a gromGenerator

    template <typename T1, typename T2, typename T3, typename T4>
    T1 orderOfElement(T2 value, T3 base, T4 MOD);

    //////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T1, typename T2, typename T3>
    T1 eulerFunction(T2 value, T3 MOD); // Euler function

    template <typename T1, typename T2, typename T3>
    T1 carmichaelFunction(T2 value, T3 MOD); // Carmichael function

    //////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T1, typename T2>
    bool isPrime(T1 value, T2 MOD); // Miller–Rabin primality test
}
