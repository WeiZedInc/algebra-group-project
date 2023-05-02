#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../pollard-factor.tcc"
#include "../isPrime.tcc"
#include <random>

#include "../../../doctest.h"
#include "utils.h"
using namespace modular;
template <class T>

bool SimpleIsPrime(T n)
{
    if (n == 2 || n == 3)
        return true;

    if (n <= 1 || n % 2 == 0 || n % 3 == 0)
        return false;

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

TEST_CASE("Testing the Miller-Rabin method to check a number for prime ") {
    using T = long long;
    SUBCASE("Edge case") {

        CHECK_EQ(isPrime(modNum<T>(-1), 100), SimpleIsPrime(1));
        CHECK_EQ(isPrime(modNum<T>(1), 100), SimpleIsPrime(1));
        CHECK_EQ(isPrime(modNum<T>(2), 100), SimpleIsPrime(2));
    }

    SUBCASE("Input from the console") {
        std::cout << "Enter the numbers you want to check for prime " << std::endl;
        T value;
        std::cin >> value;
        std::cout << "Enter the number of iterations that will set the verification accuracy" << std::endl;
        int k;
        std::cin >> k;
       CHECK_EQ( isPrime(modNum<T>(value), k), SimpleIsPrime(value));
       if (isPrime(modNum<T>(value), k))
           std::cout << "Your number is prime" << std::endl;
       else 
           std::cout << "Your number is NOT prime" << std::endl;
    }

    SUBCASE("Random values") {
        int num_errors = 0;
        for (int i = 0; i < 100000; ++i)
        {
            int value=getRandomNumber(1, 100000);
            int k = getRandomNumber(100, 1000);
            CHECK_EQ( isPrime(modNum<T>(value), k), SimpleIsPrime(value));
        }
    }

    SUBCASE("Input from the file") {

        std::fstream input;
        T value;
        int k;

        input.open("C:\\Users\\User\\Desktop\\PI-23\\Sem 2\\General Algebra\\algebra-group-project-vsc\\files\\input.txt");
        if (input.is_open()) {
            input >> value >> k;
        }
        else {
            std::cout << "File isn't open" << std::endl;
        }

        CHECK_EQ(isPrime(modNum<T>(value), k), SimpleIsPrime(value));

        std::ofstream outfile("C:\\Users\\User\\Desktop\\PI-23\\Sem 2\\General Algebra\\algebra-group-project-vsc\\files\\output.txt");
        if (outfile.is_open()) {
            if (isPrime(modNum<T>(value), k))
                outfile << "Your number is prime" << std::endl;
            else
                outfile << "Your number is NOT prime" << std::endl;

            outfile.close();
        }
        input.close();
    }
}