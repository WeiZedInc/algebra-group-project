#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../doctest.h"
#include "../mod-num.tcc"
#include "utils.h"
#include <random>

TEST_CASE("Testing modNum class with random values")
{
    using T = int;
    const int MOD = getRandomNumber(13, 200);
    modNum<T> a(getRandomNumber(1, MOD - 1), MOD);
    modNum<T> b(getRandomNumber(1, MOD - 1), MOD);

    SUBCASE("Test addition")
    {
        modNum<T> result = a + b;
        REQUIRE(result.getValue() == (a.getValue() + b.getValue()) % MOD);
    }

    SUBCASE("Test subtraction")
    {
        modNum<T> result = a - b;
        REQUIRE(result.getValue() == (a.getValue() - b.getValue() + MOD) % MOD);
    }

    SUBCASE("Test multiplication")
    {
        modNum<T> result = a * b;
        REQUIRE(result.getValue() == (a.getValue() * b.getValue()) % MOD);
    }
}