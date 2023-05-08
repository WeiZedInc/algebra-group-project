#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../poly-basic.tcc"
#include "../../../doctest.h"

using namespace modular;

TEST_CASE("Testing")
{
    SUBCASE("Test addition")
    {
        Polynomial<int> p1(5);
        p1.addNode(2, 0);
        p1.addNode(3, 1);
        p1.addNode(1, 2);

        Polynomial<int> p2(5);
        p2.addNode(1, 0);
        p2.addNode(2, 1);
        p2.addNode(4, 2);

        Polynomial<int> p3(5);
        p3.addNode(3, 0);

        REQUIRE(p3 == (p1 + p2));
    }

    SUBCASE("Test subtraction")
    {
        Polynomial<int> p1(5);
        p1.addNode(2, 0);
        p1.addNode(3, 1);
        p1.addNode(1, 2);

        Polynomial<int> p2(5);
        p2.addNode(1, 0);
        p2.addNode(2, 1);
        p2.addNode(4, 2);

        Polynomial<int> p3(5);
        p3.addNode(1, 0);
        p3.addNode(1, 1);
        p3.addNode(2, 2);

        REQUIRE(p3 == (p1 - p2));
    }

    SUBCASE("Test multiplication1")
    {
        Polynomial<int> p1(5);
        p1.addNode(3, 5);
        p1.addNode(7, 3);
        p1.addNode(2, 1);

        Polynomial<int> p2(5);
        p2.addNode(4, 4);
        p2.addNode(2, 3);
        p2.addNode(6, 1);

        Polynomial<int> p3(5);
        p3.addNode(2, 9);
        p3.addNode(1, 8);
        p3.addNode(3, 7);
        p3.addNode(2, 6);
        p3.addNode(3, 5);
        p3.addNode(1, 4);
        p3.addNode(2, 2);

        REQUIRE(p3 == (p1 * p2));
    }

    SUBCASE("Test multiplication2")
    {
        Polynomial<int> p1(5);
        p1.addNode(2, 0);
        p1.addNode(3, 1);
        p1.addNode(1, 2);

        Polynomial<int> p2(5);
        p2.addNode(1, 0);
        p2.addNode(2, 1);
        p2.addNode(4, 2);

        Polynomial<int> p3(5);
        p3.addNode(2, 0);
        p3.addNode(2, 1);
        p3.addNode(4, 3);
        p3.addNode(4, 4);

        REQUIRE(p3 == (p1 * p2));
    }
}
TEST_CASE("Testing divisionь, gcd")
{
    SUBCASE("Test 1")
    {
        Polynomial<int> p1(40);
        p1.addNode(2,4);
        p1.addNode(27,3);
        p1.addNode(36,2);
        p1.addNode(10,1);
        p1.addNode(27,0);

        Polynomial<int> p2(40);
        p2.addNode(2,1);
        p2.addNode(3,0);

        std::pair<Polynomial<int>, Polynomial<int>> res = p1 / p2;

        Polynomial<int> test = res.first * p2 + res.second;

        REQUIRE(p1 == test);
    }

    SUBCASE("Test 2")
    {
        Polynomial<int> p1(5);
        p1.addNode(3,4);
        p1.addNode(1,3);
        p1.addNode(2,2);
        p1.addNode(1,0);

        Polynomial<int> p2(5);
        p2.addNode(1,2);
        p2.addNode(4,1);
        p2.addNode(2,0);

        std::pair<Polynomial<int>, Polynomial<int>> res = p1 / p2;
        Polynomial<int> test = res.first * p2 + res.second;

        REQUIRE(p1 == test);
    }

    SUBCASE("Test 3 - divisor - constant")
    {
       Polynomial<int> p1(40);
        p1.addNode(6,4);
        p1.addNode(27,3);
        p1.addNode(36,2);
        p1.addNode(9,1);
        p1.addNode(27,0);

         Polynomial<int> p2(40);
        p2.addNode(3,0);

        std::pair<Polynomial<int>, Polynomial<int>> res = p1 / p2;

        Polynomial<int> test = res.first * p2 + res.second;

        REQUIRE(p1 == test);
    }

    SUBCASE("Test 4 - p2 empty")
    {
       Polynomial<int> p1(40);
        p1.addNode(6,4);
        p1.addNode(27,3);
        p1.addNode(36,2);
        p1.addNode(9,1);
        p1.addNode(27,0);

        Polynomial<int> p2(40);

        CHECK_THROWS_WITH(p1/p2, "Divisor must have at least one non-zero coefficient");

    }

    SUBCASE("Test 5 - numerator degree < divisor degree")
    {
        Polynomial<int> p1(40);
        p1.addNode(2,4);
        p1.addNode(27,3);
        p1.addNode(36,2);
        p1.addNode(10,1);
        p1.addNode(27,0);

        Polynomial<int> p2(40);
        p2.addNode(2,1);
        p2.addNode(3,0);
        
        CHECK_THROWS_WITH(p2/p1, "The degree of the divisor cannot exceed that of the numerator");
    }

    SUBCASE("Test 6 - gcd")
    {
        Polynomial<int> p1(2);
        p1.addNode(1,2);
        p1.addNode(1,0);


        Polynomial<int> p2(2);
        p2.addNode(1,1);
        p2.addNode(1,0);

        auto gcd = p1.gcd(p2);
        Polynomial<int> expected(2);
        expected.addNode(1,1);
        expected.addNode(1,0);
        REQUIRE(gcd == expected);
    }


}