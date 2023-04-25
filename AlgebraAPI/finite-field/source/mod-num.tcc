#ifndef TASK2_TCC
#define TASK2_TCC
#include <iostream>
#include <cassert>

template<typename T>
class modNum {
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
    T add(T value1, T value2, T MOD) const{
        if (MOD <= 0) {
            throw std::invalid_argument("modulus should be positive");
        }
        T result = value1 + value2;
        result %= MOD;
        if (result < 0) {
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
    T subs(T value1, T value2, T MOD) const {
        if (MOD <= 0) {
            throw std::invalid_argument("modulus should be positive");
        }
        T result = value1 - value2;
        result %= MOD;
        if (result < 0) {
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

    T mult(T value1, T value2, T MOD) const {
        if (MOD <= 0) {
            throw std::invalid_argument("modulus should be positive");
        }
        value1 = (value1 % MOD + MOD) % MOD;
        value2 = (value2 % MOD + MOD) % MOD;
        T result = 0;
        while (value2) {
            if (value2 & 1) {
                result = (result + value1) % MOD;
            }
            value1 = (value1 * 2) % MOD;
            value2 >>= 1;
        }
        return result;
    }

public:
    T getValue() const { // method to access private member value
        return value;

    }

    void setMod(T MOD) {
        if (MOD <= 0) {
            throw std::invalid_argument("modulus should be positive");
        }
        this->MOD = MOD;
    }

    modNum(T value = 0, T MOD = 1) : value(value), MOD(MOD) {
        if (MOD <= 0) {
            throw std::invalid_argument("modulus should be positive");
        }
    }
    modNum operator+(const modNum& other) const {
        return modNum(add(value, other.value, MOD), MOD);
    }
    modNum operator-(const modNum& other) const {
        return modNum(subs(value, other.value, MOD), MOD);
    }
    modNum operator*(const modNum& other) const {
        return modNum(mult(value, other.value, MOD), MOD);
    }
};

#endif // TASK2_TCC


