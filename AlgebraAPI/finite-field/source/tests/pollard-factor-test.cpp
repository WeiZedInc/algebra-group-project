#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../doctest.h"
#include "../pollard-factor.tcc"
#include "utils.h"
#include <random>


TEST_CASE("Testing Pollard factorization")
{
    using T = long long;
    SUBCASE("Test1")
    {
       std::vector<modNum<T>> f1 = factorize(modNum<T>(10403));
       std::vector<modNum<T>> factors1{modNum<T>(101), modNum<T>(103)};
       REQUIRE(f1 == factors1);

       std::vector<modNum<T>> f2 = factorize(modNum<T>(121));
       std::vector<modNum<T>> factors2{modNum<T>(11), modNum<T>(11)};
       REQUIRE(f2 == factors2);

       std::vector<modNum<T>> f3 = factorize(modNum<T>(433));
       std::vector<modNum<T>> factors3{modNum<T>(433)};
       REQUIRE(f3 == factors3);

       std::vector<modNum<T>> f4 = factorize(modNum<T>(1232));
       std::vector<modNum<T>> factors4{modNum<T>(2), modNum<T>(2), modNum<T>(2), modNum<T>(2), modNum<T>(7), modNum<T>(11)};
       REQUIRE(f4 == factors4);
    }

    SUBCASE("Test2")
    {
        for (long long i = 2; i <= 100000; ++i) 
        {
            bool isExceptionThrown = false;
            try 
            {
                std::vector<modNum<T>> num1 = factorize(modNum<T>(i));
            }
            catch (std::exception &e)
            {
                isExceptionThrown = true;
            }
            REQUIRE(!isExceptionThrown);
        }
    }

    SUBCASE("Test3")
    {
        modNum<T> a(getRandomNumber(1, getRandomNumber(1, 100000)));

        std::vector<modNum<T>> f1 = factorize(a);

        T mult = 1;
        bool isExceptionThrown = false;
        for (auto numb : f1)
        {
            if (!isPrime(numb.getValue()))
                break;
            mult *= numb.getValue();
        }

        REQUIRE(a.getValue() == mult);
    }

   
}