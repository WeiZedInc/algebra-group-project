#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../doctest.h"
#include "../../mod-math.h"
#include "utils.h"
#include <random>

using namespace modular;


TEST_CASE("randomized test 1..1000 with mod 13") {
    for (int i = 0; i < 1000; ++i) {
        int num = getRandomNumber(1, 10000000);
        int pw = getRandomNumber(1, 1000);

        CHECK_EQ(fpow(modNum(num, 47), pw).getValue(), logPow(num, pw, 47));
    }
}
