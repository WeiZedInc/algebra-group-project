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

    SUBCASE("Test long division")
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

    SUBCASE("Test 2 long division")
    {
        Polynomial<int> p1(11);
        p1.addNode(5,1);
        p1.addNode(10,0);

         Polynomial<int> p2(11);
        p2.addNode(5,0);

        std::pair<Polynomial<int>, Polynomial<int>> res = p1 / p2;

        Polynomial<int> test = res.first * p2 + res.second;

        REQUIRE(p1 == test);
    }
}