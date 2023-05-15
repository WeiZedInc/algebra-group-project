#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <iostream>
#include <vector>
#include "../circular-polynomial.hpp"
#include "../../poly-ring-math.h"
#include "../../../doctest.h"

//int main() {
//    auto v = Polynomial<long long int>::getCyclotomicPolynomial(12, 5);
//    v.print();
//    return 0;
//}

DOCTEST_TEST_CASE("Cyclotomic Polynomial Test") {
    DOCTEST_SUBCASE("Prime N") {
        std::vector<int32_t> result = getCyclotomicPolynomialRaw(17);
        std::vector<int32_t> expected = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        DOCTEST_CHECK(result == expected);
    }

    DOCTEST_SUBCASE("Small values") {
        // N = 1
        std::vector<int32_t> result = getCyclotomicPolynomialRaw(1);
        CHECK_EQ(result, std::vector<int32_t>({1, -1}));

        // N = 2
        result = getCyclotomicPolynomialRaw(2);
        CHECK_EQ(result, std::vector<int32_t>({1, 1}));

        // N = 3
        result = getCyclotomicPolynomialRaw(3);
        CHECK_EQ(result, std::vector<int32_t>({1, 1, 1}));

        // N = 4
        result = getCyclotomicPolynomialRaw(4);
        CHECK_EQ(result, std::vector<int32_t>({1, 0, 1}));

        // N = 5
        result = getCyclotomicPolynomialRaw(5);
        CHECK_EQ(result, std::vector<int32_t>({1, 1, 1, 1, 1}));

        // N = 6
        result = getCyclotomicPolynomialRaw(6);
        CHECK_EQ(result, std::vector<int32_t>({1, -1, 1}));
    }

    DOCTEST_SUBCASE("Cyclotomic Polynomial test, large values") {
        // N = 10
        std::vector<int32_t> result = getCyclotomicPolynomialRaw(10);
        CHECK_EQ(result, std::vector<int32_t>({1, -1, 1, -1, 1}));

        // N = 15
        result = getCyclotomicPolynomialRaw(15);
        CHECK_EQ(result, std::vector<int32_t>({1, -1, 0, 1, -1, 1, 0, -1, 1}));

        // N = 20
        result = getCyclotomicPolynomialRaw(20);
        CHECK_EQ(result, std::vector<int32_t>({1, 0, -1, 0, 1, 0, -1, 0, 1}));

        // N = 30
        result = getCyclotomicPolynomialRaw(30);
        CHECK_EQ(result, std::vector<int32_t>({1, 1, 0, -1, -1, -1, 0, 1, 1}));
    }
}
