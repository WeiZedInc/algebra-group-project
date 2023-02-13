#include "mod-int.h"

#include <vector>
#include <string>

namespace modular
{
    __int128_t add(__int128_t value1, __int128_t value2, __int128_t MOD); // addition

    __int128_t subs(__int128_t value1, __int128_t value2, __int128_t MOD); // substruction

    __int128_t mult(__int128_t value1, __int128_t value2, __int128_t MOD); // multyplication

    ////////////////////////////////////////////////////////////////////////////////////////////

    __int128_t div(__int128_t value1, __int128_t value2, __int128_t MOD); // division

    __int128_t inv(__int128_t value1, __int128_t MOD); // inverse element

    /////////////////////////////////////////////////////////////////////////////////////////////

    __int128_t pow(__int128_t value, __int128_t base, __int128_t MOD); // regular pow

    __int128_t fpow(__int128_t value, __int128_t base, __int128_t MOD); // fast pow

    //////////////////////////////////////////////////////////////////////////////////////////////

    std::vector<__int128_t> factorize(__int128_t value, __int128_t MOD); // number factorization using Polard algorithm

    std::vector<__int128_t> naiveFactorize(__int128_t value, __int128_t MOD); // naive number factorization

    //////////////////////////////////////////////////////////////////////////////////////////////

    __int128_t log(__int128_t value, __int128_t base, __int128_t MOD); // discrete logarithm

    //////////////////////////////////////////////////////////////////////////////////////////////

    // needs clarifications
    bool isGenrator(__int128_t value, std::string operation, __int128_t MOD); // is element a gromGenerator

    __int128_t orderOfElement(__int128_t value, __int128_t base, __int128_t MOD);

    //////////////////////////////////////////////////////////////////////////////////////////////

    __int128_t eulerFunction(__int128_t value, __int128_t MOD);      // Euler function
    __int128_t carmichaelFunction(__int128_t value, __int128_t MOD); // Carmichael function

    //////////////////////////////////////////////////////////////////////////////////////////////
    bool isPrime(__int128_t value, __int128_t MOD); // Miller–Rabin primality test
}
