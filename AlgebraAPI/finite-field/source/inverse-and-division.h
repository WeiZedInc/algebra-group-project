// Function for extended Euclidean Algorithm
#include <stdexcept>

namespace modular
{
    template <typename num>
    num gcdExtended(num a, num b, num *x, num *y)
    {
        // Base Case
        if (a == 0)
        {
            *x = 0;
            *y = 1;
            return b;
        }
        num x1, y1; // To store results of recursive call
        num gcd = gcdExtended(b % a, a, &x1, &y1);
        // Update x and y using results of
        // recursive call
        *x = y1 - (b / a) * x1;
        *y = x1;
        return gcd;
    }

    /**
     *  @brief Inverses the given element in a modular field
     *  @param  value1 element to be inversed
     *  @param MOD  module
     *
     *  @return returns inversed element
     */

    template <typename num>
    num inv(num value1, num MOD)
    {
        num x, y;

        num g = gcdExtended(value1, MOD, &x, &y);
        if (g != 1)
        {
            throw std::invalid_argument("Write something here");
        }
        else
        {
            x = (x % MOD + MOD) % MOD;
            return x;
        }
    }

    /**
     *  @brief divides value1 by value2 in a modular field
     *  @param  value1 numerator
     *  @param  value2 denominator
     *  @param MOD  module
     *
     *
     *  complexity O(log(n))
     *  @return returns result of division
     */

    template <typename num>
    num div(num value1, num value2, num MOD)
    {
        return value1 * inv(value2, MOD);
    }
}