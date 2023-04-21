#include <vector>
#include <string>

namespace modular
{
 template <typename T1>
    T1 add(T1 value1, T1 value2, T1 MOD); // addition

 template <typename T1>
    T1 subs(T1 value1, T1 value2, T1 MOD); // substruction

 template <typename T1>
    T1 mult(T1 value1, T1 value2, T1 MOD); // multyplication

    ////////////////////////////////////////////////////////////////////////////////////////////
 template <typename T1>
    T1 div(T1 value1, T1 value2, T1 MOD); // division
    template <typename T1>
    T1 inv(T1 value1, T1 MOD); // inverse element

    /////////////////////////////////////////////////////////////////////////////////////////////
 template <typename T1>
    T1 pow(T1 value, T1 base, T1 MOD); // regular pow
 template <typename T1>
    T1 fpow(T1 value, T1 base, T1 MOD); // fast pow

    //////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T1>
    std::vector<T1> factorize(T1 value, T1 MOD); // number factorization using Polard algorithm
    template <typename T1>T//
 template <typename T1>
    T1 log(T1 value, T1 base, T1 MOD); // discrete logarithm

    //////////////////////////////////////////////////////////////////////////////////////////////

    // needs clarifications
    template <typename T1>
    bool isGenrator(T1 value, std::string operation, T1 MOD); // is element a gromGenerator

 template <typename T1>
    T1 orderOfElement(T1 value, T1 base, T1 MOD);

    //////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T1>
    T1 eulerFunction(T1 value, T1 MOD); // Euler function

    template <typename T1>
    T1 carmichaelFunction(T1 value, T1 MOD); // Carmichael function

    //////////////////////////////////////////////////////////////////////////////////////////////
    template <typename T1>
    bool isPrime(T1 value, T1 MOD); // Miller–Rabin primality test
}
