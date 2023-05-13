#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../doctest.h"
#include "../../mod-math.h"
#include "utils.h"
#include <random>

using namespace modular;

template <class T>
T
logPow(T base, T power, T MOD) {
    T result = 1;
    while (power > 0) {
        if (power % 2 == 1) {   // Can also use (power & 1) to make code even faster
            result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
        power = power / 2;   // Can also use power >>= 1; to make code even faster
    }
    return result;
}

/*TEST_CASE("randomized test 1..1000 with mod 13") {
    for (int i = 0; i < 1000; ++i) {
        int num = getRandomNumber(1, 1000);
        int pw = getRandomNumber(1, 1000);

        // CHECK_EQ(fpow(modNum(num, 47), pw).getValue(), logPow(num, pw, 47));
    }
}*/
