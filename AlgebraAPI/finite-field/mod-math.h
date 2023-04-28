#include <string>
#include <vector>

namespace modular {
#ifndef MOD_NUM
#define MOD_NUM
template <typename T>
class modNum {
   private:
    mutable T value, MOD;

    T add(T value1, T value2, T MOD) const;
    T subs(T value1, T value2, T MOD) const;
    T mult(T value1, T value2, T MOD) const;
    T gcdExtended(T a, T b, T *x, T *y) const;
    T inverseValue(T value1, T mod) const;
    T div(T value1, T value2, T mod) const;

   public:
    modNum(T value = 0, T MOD = 1) : value(value), MOD(MOD) {
        if (MOD <= 0) {
            throw std::invalid_argument("modulus should be positive");
        }
    }

    T getValue() const;
    T getMod() const { return MOD; };
    void setMod(T MOD);

    bool operator==(const modNum &other) const {
        return value == other.value && MOD == other.MOD;
    }

    bool operator<(const modNum &other) const { return value < other.value; }

    bool operator<=(const modNum &other) const { return value <= other.value; }

    bool operator>(const modNum &other) const { return value > other.value; }

    bool operator>=(const modNum &other) const { return value >= other.value; }

    modNum inv();

    modNum<T> operator+(const modNum &other) const;
    modNum<T> operator-(const modNum &other) const;
    modNum<T> operator*(const modNum &other) const;
    modNum<T> operator/(const modNum &other) const;
};
#endif

/////////////////////////////////////////////////////////////////////////////////////////////
template <typename T1>
modNum<T1> pow(modNum<T1> value, modNum<T1> base,
               modNum<T1> MOD);   // regular pow
template <typename T1>
modNum<T1> fpow(modNum<T1> value, modNum<T1> base,
                modNum<T1> MOD);   // fast pow

//////////////////////////////////////////////////////////////////////////////////////////////
template <typename T1>
std::vector<modNum<T1>> factorize(
    modNum<T1> value);   // number factorization using Polard algorithm

//////////////////////////////////////////////////////////////////////////////////////////////

template <typename T1>
modNum<T1> sqrt(modNum<T1> value);   // discrete square root

//////////////////////////////////////////////////////////////////////////////////////////////

template <typename T1>
modNum<T1> log(modNum<T1> value, modNum<T1> base);   // discrete logarithm

//////////////////////////////////////////////////////////////////////////////////////////////

// needs clarifications
template <typename T1>
bool isGenrator(modNum<T1> value,
                std::string operation);   // is element a group generator

template <typename T1>
size_t orderOfElement(modNum<T1> value, modNum<T1> base);

//////////////////////////////////////////////////////////////////////////////////////////////
template <typename T1>
modNum<T1> eulerFunction(modNum<T1> value);   // Euler function

template <typename T1>
modNum<T1> carmichaelFunction(modNum<T1> value);   // Carmichael function

//////////////////////////////////////////////////////////////////////////////////////////////
template <typename T1>
bool isPrime(modNum<T1> value, size_t k);   // Miller–Rabin primality test

}   // namespace modular

#include "source/mod-num.tcc"