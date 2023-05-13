#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../pollard-factor.tcc"

#include <random>

#include "../../../doctest.h"
#include "utils.h"
using namespace modular;

TEST_CASE("Testing Pollard factorization") {
    using T = long long;

    SUBCASE("Test1") {
        T mod = 16323010999;
        
        std::vector<modNum<T>> pf0 = factorize(modNum<T>(4853343967, mod));
        std::vector<modNum<T>> factors0{modNum<T>(55817, mod), modNum<T>(86951, mod)};
        sort(pf0.begin(), pf0.end());
        REQUIRE(pf0 == factors0);

        std::vector<modNum<T>> pf1 = factorize(modNum<T>(10403, mod));
        std::vector<modNum<T>> factors1{modNum<T>(101, mod), modNum<T>(103, mod)};
        sort(pf1.begin(), pf1.end());
        REQUIRE(pf1 == factors1);

        std::vector<modNum<T>> pf2 = factorize(modNum<T>(121, mod));
        std::vector<modNum<T>> factors2{modNum<T>(11, mod), modNum<T>(11, mod)};
        REQUIRE(pf2 == factors2);

        std::vector<modNum<T>> pf3 = factorize(modNum<T>(433, mod));
        std::vector<modNum<T>> factors3{modNum<T>(433, mod)};
        REQUIRE(pf3 == factors3);

        std::vector<modNum<T>> pf4 = factorize(modNum<T>(1232, mod+1));
        sort(pf4.begin(), pf4.end());
        std::vector<modNum<T>> factors4{modNum<T>(2, mod+1), modNum<T>(2, mod+1), modNum<T>(2, mod+1),
                                        modNum<T>(2, mod+1), modNum<T>(7, mod+1), modNum<T>(11, mod+1)};
        REQUIRE(pf4 == factors4);
    }

    SUBCASE("Test2") {
        for (long long i = 2; i <= 100000; ++i) {
            bool isExceptionThrown = false;
            try {
                std::vector<modNum<T>> num1 = factorize(modNum<T>(i, i+1));

            } catch (std::exception &e) {
                isExceptionThrown = true;
            }
            REQUIRE(!isExceptionThrown);
        }
    }

    SUBCASE("Test3") {
        T mod = getRandomNumber(1, getRandomNumber(1, 100000));
        modNum<T> a(getRandomNumber(1, getRandomNumber(1, 100000)), mod);

        std::vector<modNum<T>> f1 = factorize(a);

        modNum<T> mult (1,mod);
        bool isExceptionThrown = false;
        for (auto numb : f1) {
            if (!isPrimeSimple(numb.getValue()))
                break;
            mult = mult * numb;
        }

        REQUIRE(a == mult);
    }
}