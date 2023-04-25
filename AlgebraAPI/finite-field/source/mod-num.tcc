#ifndef TASK2_TCC
#define TASK2_TCC
#include <iostream>
#include <cassert>

template <typename T>
class modNum
{
private:
    mutable T value, MOD;
    /**
     * @brief Adds two values modulo MOD.
     * @param  value1 the first value to add
     * @param  value2 The second value to add.
     * @param MOD  The modulo value
     * @return The sum of the two values modulo MOD
     * @throws std::invalid_argument if MOD is non - positive
     */
    T add(T value1, T value2, T MOD) const
    {
        if (MOD <= 0)
        {
            throw std::invalid_argument("modulus should be positive");
        }
        T result = value1 + value2;
        result %= MOD;
        if (result < 0)
        {
            result += MOD;
        }
        return result;
    }
    /**
     *  @brief Subtract two values modulo MOD.
     *  @param  value1 the first value to be subtracted.
     *  @param  value2 The second value to be subtracted.
     *  @param MOD The modulo value
     *  @return The result of the subtraction with modulo operation.
     *  @throws std::invalid_argument if MOD is non-positive
     */
    T subs(T value1, T value2, T MOD) const
    {
        if (MOD <= 0)
        {
            throw std::invalid_argument("modulus should be positive");
        }
        T result = value1 - value2;
        result %= MOD;
        if (result < 0)
        {
            result += MOD;
        }
        return result;
    }
    /**
     *  @brief Multiply two values modulo MOD.
     *  @param  value1 the first value to multiply.
     *  @param  value2 The second value to multiply.
     *  @param MOD The modulo value
     *  @return The result of the multipilcation with modulo operation.
     *  @throws std::invalid_argument if MOD is non-positive
     */

    T mult(T value1, T value2, T MOD) const
    {
        if (MOD <= 0)
        {
            throw std::invalid_argument("modulus should be positive");
        }
        value1 = (value1 % MOD + MOD) % MOD;
        value2 = (value2 % MOD + MOD) % MOD;
        T result = 0;
        while (value2)
        {
            if (value2 & 1)
            {
                result = (result + value1) % MOD;
            }
            value1 = (value1 * 2) % MOD;
            value2 >>= 1;
        }
        return result;
    }

    T gcdExtended(T a, T b, T *x, T *y) const
    {
        // Base Case
        if (a == 0)
        {
            *x = 0;
            *y = 1;
            return b;
        }
        T x1, y1; // To store results of recursive call
        T gcd = gcdExtended(b % a, a, &x1, &y1);
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

    T inverseValue(T value1, T mod) const
    {
        T x, y;

        T gcdResult = gcdExtended(value1, mod, &x, &y);
        if (gcdResult != 1)
        {
            std::string errormsg = "Inverse does not exist here. g: " + std::to_string(gcdResult) + " value1: " + std::to_string(value1) + " mod: " + std::to_string(mod);
            throw std::invalid_argument(errormsg);
        }
        else
        {
            x = (x % mod + mod) % mod;
            return x;
        }
    }

    /**
     *  @brief divides value1 by value2 in a modular field
     *  @param  value1 Terator
     *  @param  value2 denominator
     *  @param MOD  module
     *
     *
     *  complexity O(log(n))
     *  @return returns result of division
     */

    T div(T value1, T value2, T mod) const
    {
        return value1 * inverseValue(value2, mod);
    }

public:
    T getValue() const
    { // method to access private member value
        return value;
    }

    void setMod(T MOD)
    {
        if (MOD <= 0)
        {
            throw std::invalid_argument("modulus should be positive");
        }
        this->MOD = MOD;
    }

    modNum(T value = 0, T MOD = 1) : value(value), MOD(MOD)
    {
        if (MOD <= 0)
        {
            throw std::invalid_argument("modulus should be positive");
        }
    }
    modNum inv()
    {
        return modNum(inverseValue(value, MOD), MOD);
    }

    modNum<T> operator+(const modNum &other) const
    {
        return modNum<T>(add(value, other.value, MOD), MOD);
    }
    modNum<T> operator-(const modNum &other) const
    {
        return modNum<T>(subs(value, other.value, MOD), MOD);
    }
    modNum<T> operator*(const modNum &other) const
    {
        return modNum<T>(mult(value, other.value, MOD), MOD);
    }

    modNum<T> operator/(const modNum &other) const
    {
        return modNum<T>(div(value, other.value, MOD), MOD);
    }
};

#endif // TASK2_TCC
