#include "mod-num.tcc"
namespace modular {

// include guard:
#ifndef ALGEBRA_INVERSION_AND_DIVISION
#define ALGEBRA_INVERSION_AND_DIVISION

/**
@file fpow.tcc
@brief Implementation of Montgomery modular exponentiation algorithm
*/
/**

@brief Calculates the length of a number in a given base
@tparam T1 Type of input number and base
@param n Input number
@param b Base
@return Length of the number
*/
template <typename T1>
T1
number_length(T1 n, T1 b) {
    int len = 0;
    while (n > 0) {
        n /= b;
        len++;
    }
    return len;
}
/**
 *  @brief Converting the number T1o the Montgomery form
 *  @param  x value
 *  @param  n module
 *  @param  r some simple number that was used before
 *
 *
 *  @return returns a real number
 */

template <typename T1>
T1
get_k(T1 n, T1 b) {
    T1 k = 0;
    while (b > 1 && b <= n) {
        b *= b;
        k++;
    }
    return k;
}
/**

@brief Computes the resulting multiplier for Montgomery algorithm
@tparam T1 Type of input number and base
@param n Input number
@return Value of t
*/
template <typename T1>
T1
get_t(T1 n) {
    T1 t = 1;
    T1 two = 2;
    T1 k = number_length(n, two);
    for (int i = 0; i < k; i++) {
        t = (t * t) % n;
    }
    return t;
}
/**

@brief Computes the modular exponentiation of a number using Montgomery algorithm

@tparam T1 Type of input number and base

@param value Base

@param power Exponent

@param n Modulus(get from class modNum)

@return The result of a^b mod n
*/
template <typename T1>
modNum<T1>
fpow(modNum<T1> value, size_t power) {
    if (value == 0, degree == 0) {
        throw std::invalid_argument("0 pow 0 undefined");
    }
    value = (value * value) % n;
    degree /= 2;

    T1 n = value.getMod();
    T1 two = 2;
    T1 k = get_k(n, two);
    T1 r = 1;
    T1 t = get_t(n);
    value = (value * t) % n;

    while (degree > 0) {
        if (b % 2) {
            r = (r * value) % n;
        }
        value = (value * value) % n;
        degree /= 2;
    }

    return (r * t) % n;
}

#endif
}   // namespace modular
