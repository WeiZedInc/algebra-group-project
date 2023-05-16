#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../../../doctest.h"
#include "../../poly-field-math.h"

TEST_CASE("Test addition 1") {
    std::vector<std::pair<int, size_t>> arrrr = {{3, 3}, {4, 2}, {5, 1}, {6, 0}};
    std::vector<std::pair<int, size_t>> mod = {{7, 7}};

    PolynomialField<int> pol1(11, mod, arrrr);

    std::vector<std::pair<int, size_t>> arrrr2 = {{3, 3}, {4, 2}, {5, 1}, {6, 0}};

    PolynomialField<int> pol2(11, mod, arrrr2);

    PolynomialField<int> pol3 = pol1 + pol2;

    pol3.print();
}
TEST_CASE("Test multiplication 1") {}

TEST_CASE("Test multiplication 2") {}

TEST_CASE("Test pow") {}
