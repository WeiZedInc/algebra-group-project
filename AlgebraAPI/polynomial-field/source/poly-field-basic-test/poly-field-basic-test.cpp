#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../poly-field-basic.tcc"
#include "../../../doctest.h"

TEST_CASE("Testing")
{
    SUBCASE("Test addition 1")
    {
        PolynomialField<int> p1(4, 3);
        p1.addNode(1, 0);
        p1.addNode(3, 1);
        p1.addNode(2, 2);
        PolynomialField<int> p2(4, 3);
        p2.addNode(2, 0);
        p2.addNode(1, 1);
        p2.addNode(3, 2);
        PolynomialField<int> p3(4, 3);
        p3 = p1 + p2;
        PolynomialField<int> p(4, 3);
        p.addNode(1, 2);
        p.addNode(3, 0);
        REQUIRE(p3 == p);
    }
    SUBCASE("Test multiplication 1")
    {
        PolynomialField<int> p1(4, 3);
        p1.addNode(1, 0);
        p1.addNode(3, 1);
        p1.addNode(2, 2);
        PolynomialField<int> p2(4, 3);
        p2.addNode(2, 0);
        p2.addNode(1, 1);
        p2.addNode(3, 2);
        PolynomialField<int> p(4, 3);
        p.addNode(3, 2);
        p.addNode(1, 1);
        p.addNode(1, 0);
        PolynomialField<int> p3(4, 3);
        p3 = p1 * p2;
        REQUIRE(p3 == p);
    }
    SUBCASE("Test multiplication 2")
    {
        PolynomialField<int> p1(4, 3);
        p1.addNode(1, 0);
        p1.addNode(3, 1);
        p1.addNode(2, 2);
        PolynomialField<int> p2(4, 3);
        p2 = p1 * 0.5;
        PolynomialField<int> p(4, 3);
        p.addNode(0.5, 0);
        p.addNode(1.5, 1);
        p.addNode(1, 2);
        REQUIRE(p == p2);
    }
    SUBCASE("Test pow")
    {
        PolynomialField<int> p(3, 3);
        p.addNode(2, 1);
        p.addNode(2, 0);
        PolynomialField<int> p1(3, 3);
        p1.addNode(1, 2);
        p1.addNode(2, 1);
        p1.addNode(1, 0);
        PolynomialField<int> p2(3, 3);
        p2 = p1.pow(2);
        REQUIRE(p == p2);
    }
}
