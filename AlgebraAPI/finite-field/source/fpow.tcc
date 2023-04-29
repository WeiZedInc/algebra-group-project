#include "mod-num.tcc"
namespace modular {

// include guard:
#ifndef ALGEBRA_INVERSION_AND_DIVISION
#define ALGEBRA_INVERSION_AND_DIVISION

/**
 *  @brief Converting the number T1o the Montgomery form
 *  @param  x value
 *  @param  n module
 *  @param  r some simple number
 *
 *
 *  @return returns a number in Montgomery form
 */
template <typename T1>
T1
toMontgomery(T1 x, T1 n, T1 r) {
    return (x * r) % n;
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
fromMontgomery(T1 x, T1 n, T1 r) {
    T1 inv_r = 0;
    T1 q = 0;
    T1 r1 = 1;
    T1 r2 = 0;
    T1 a = n;

    while (r != 0) {
        q = a / r;
        r2 = r1 - q * r2;
        r1 = r;
        r = r2;

        inv_r = inv_r * (-q) + r2;
        inv_r = inv_r ^ (r1 - 1) * (r1 % 2);
        a = r;
        r = n % r;
    }

    if (x > n)
        return fromMontgomery(x % n, n, r);

    return (x * inv_r) % n;
}

/**
 *  @brief Raises a number to a power
 *  @param  value value
 *  @param  base degree
 *  @param  MOD module
 *
 *
 *  @return returns a result
 */
template <typename T1>
modNum<T1>
fpow(modNum<T1> base, int32_t power) {
    /*
      T1 r = 1 << 16;

      T1 result = toMontgomery(1, MOD, r);
      value = toMontgomery(value, MOD, r);

      while (base > 0)
      {
          if (base % 2 == 1)
          {
              result = (result * value) % MOD;
          }

          value = (value * value) % MOD;
          base = base / 2;
      }

      return fromMontgomery(result, MOD, r);
    */
    T1 result = 1;
    T1 baseVal = base.getValue();
    while (power > 0) {
        if (power % 2 == 1) {   // Can also use (power & 1) to make code even faster
            result = (result * baseVal) % base.getMod();
        }
        baseVal = (baseVal * baseVal) % base.getMod();
        power = power / 2;   // Can also use power >>= 1; to make code even faster
    }
    return modNum(result, base.getMod());
}

#endif
}