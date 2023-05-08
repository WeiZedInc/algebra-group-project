
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../fpow.tcc"

#include <iostream>

#include "../../../doctest.h"
#include "utils.h"
using namespace modular;

template <class T>
T logPow(T base, T power, T MOD) {
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

TEST_CASE("fpow - random values") {
    modNum<int> a = getRandomNumber(1,1000);
    int b = getRandomNumber(1,1000);

    for(int i = 1; i <= 100; i++){
        CHECK_EQ(fpow(a, b),logPow(a,b,a.getMod()));
    }

}