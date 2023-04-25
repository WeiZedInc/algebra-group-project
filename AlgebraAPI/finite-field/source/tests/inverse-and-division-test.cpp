#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "../../../doctest.h"
#include <vector>
#include <random>
#include "../inverse-and-division.tcc"
#include "utils.h"

using namespace std;
using namespace modular;

TEST_CASE("Inverse and division test")
{
    SUBCASE("Inversion test")
    {
        for (int i = 0; i < 100; i++)
        {
            int mod = getRandomPrimeNumber(1, 100);
            int num = getRandomNumber(1, mod - 1);

            int x, y;

            CHECK_EQ((num * inv(num, mod)) % mod, 1);
        }
    }
}