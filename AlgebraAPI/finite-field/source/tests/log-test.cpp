#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../log.tcc"

#include <random>

#include "../../../doctest.h"
#include "../fpow.tcc"
#include "utils.h"

using namespace modular;

TEST_CASE("tmp") {
    int mod = 113;
    for (int i = 0; i < 1000; ++i) {
        modNum<int> a(getRandomNumber(1, 112), mod), b(getRandomNumber(1, 112), mod);

        CHECK_EQ(a.getValue(), fpow(b, modular::log(a, b)).getValue());
    }
}