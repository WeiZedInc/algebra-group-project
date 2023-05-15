#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <iostream>
#include <vector>
#include "../circular-polynomial.hpp"
#include "../../../doctest.h"

using namespace modular;

//int main() {
//    auto start = std::chrono::high_resolution_clock::now();
//    //for (int32_t i = 1; i <= 8; ++i) {
//    auto v = cyclotomic_polynomial(105);
//    std::cout << 105 << ": " << v << '\n';
//    //}
//    std::reverse(v.begin(), v.end());
//    auto end = std::chrono::high_resolution_clock::now();
//    std::cout << " -> " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
//    return 0;
//}

DOCTEST_TEST_CASE("Cyclotomic Polynomial Test") {
    DOCTEST_SUBCASE("Prime N") {
        std::vector<int32_t> result = cyclotomic_polynomial(17);
        std::vector<int32_t> expected = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        DOCTEST_CHECK(result == expected);
    }

    DOCTEST_SUBCASE("Small values") {
        // N = 1
        std::vector<int32_t> result = cyclotomic_polynomial(1);
        CHECK_EQ(result, std::vector<int32_t>({1, -1}));

        // N = 2
        result = cyclotomic_polynomial(2);
        CHECK_EQ(result, std::vector<int32_t>({1, 1}));

        // N = 3
        result = cyclotomic_polynomial(3);
        CHECK_EQ(result, std::vector<int32_t>({1, 1, 1}));

        // N = 4
        result = cyclotomic_polynomial(4);
        CHECK_EQ(result, std::vector<int32_t>({1, 0, 1}));

        // N = 5
        result = cyclotomic_polynomial(5);
        CHECK_EQ(result, std::vector<int32_t>({1, 1, 1, 1, 1}));

        // N = 6
        result = cyclotomic_polynomial(6);
        CHECK_EQ(result, std::vector<int32_t>({1, -1, 1}));
    }

    DOCTEST_SUBCASE("Cyclotomic Polynomial test, large values") {
        // N = 10
        std::vector<int32_t> result = cyclotomic_polynomial(10);
        CHECK_EQ(result, std::vector<int32_t>({1, -1, 1, -1, 1}));

        // N = 15
        result = cyclotomic_polynomial(15);
        CHECK_EQ(result, std::vector<int32_t>({1, -1, 0, 1, -1, 1, 0, -1, 1}));

        // N = 20
        result = cyclotomic_polynomial(20);
        CHECK_EQ(result, std::vector<int32_t>({1, 0, -1, 0, 1, 0, -1, 0, 1}));

        // N = 30
        result = cyclotomic_polynomial(30);
        CHECK_EQ(result, std::vector<int32_t>({1, 1, 0, -1, -1, -1, 0, 1, 1}));
    }
}
