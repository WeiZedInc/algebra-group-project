// Function for extended Euclidean Algorithm
#include <stdexcept>

//include guard:
#ifndef ALGEBRA_INVERSION_AND_DIVISION
#define ALGEBRA_INVERSION_AND_DIVISION
namespace modular
{
    template <typename num>
    num gcdExtended(num a, num b, num* x, num* y)
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

//failed alt attempt
/*
     // Computes the modular inverse of a modulo m using the extended Euclidean algorithm
    template <typename num>
    num inv_alt_new(num a, num m) {
        int r = a % m, t, q, x0 = 0, x1 = 1;
        while (r != 0) {
            q = a / r;
            t = r; r = a % r; a = t;
            t = x0; x0 = x1 - q * x0; x1 = t;
        }
        if (x1 < 0) x1 += m;
        return x1;
    }
*/

    template <typename num>
    num inv(num value1, num MOD)
    {
        num x, y;

        num g = gcdExtended(value1, MOD, &x, &y);
        if (g != 1)
        {
            std::string errormsg = "Inverse does not exist here. g: " + std::to_string(g) + " value1: " + std::to_string(value1) + " mod: " + std::to_string(MOD);
            throw std::invalid_argument(errormsg);
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
#endif