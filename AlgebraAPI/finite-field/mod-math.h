#include <vector>
#include <string>

namespace modular
{
#ifndef MOD_NUM
#define MOD_NUM
   template <typename T>
   class modNum
   {
   private:
      mutable T value, MOD;

      T add(T value1, T value2, T MOD) const;
      T subs(T value1, T value2, T MOD) const;
      T mult(T value1, T value2, T MOD) const;
      T gcdExtended(T a, T b, T *x, T *y) const;
      T inverseValue(T value1, T mod) const;
      T div(T value1, T value2, T mod) const;

   public:
      T getValue() const;
      void setMod(T MOD);
      modNum(T value = 0, T MOD = 1) : value(value), MOD(MOD)
      {

         if (MOD <= 0)
         {
            throw std::invalid_argument("modulus should be positive");
         }
      }

      modNum inv();

      modNum<T> operator+(const modNum &other) const;
      modNum<T> operator-(const modNum &other) const;
      modNum<T> operator*(const modNum &other) const;
      modNum<T> operator/(const modNum &other) const;
   };
#endif

   /////////////////////////////////////////////////////////////////////////////////////////////
   template <typename T1>
   T1 pow(T1 value, T1 base, T1 MOD); // regular pow
   template <typename T1>
   T1 fpow(T1 value, T1 base, T1 MOD); // fast pow

   //////////////////////////////////////////////////////////////////////////////////////////////
   template <typename T1>
   std::vector<T1> factorize(T1 value, T1 MOD); // number factorization using Polard algorithm

   //////////////////////////////////////////////////////////////////////////////////////////////

   template <typename T1>
   T1 log(T1 value, T1 base, T1 MOD); // discrete logarithm

   //////////////////////////////////////////////////////////////////////////////////////////////

   // needs clarifications
   template <typename T1>
   bool isGenrator(T1 value, std::string operation, T1 MOD); // is element a gromGenerator

   template <typename T1>
   T1 orderOfElement(T1 value, T1 base, T1 MOD);

   //////////////////////////////////////////////////////////////////////////////////////////////
   template <typename T1>
   T1 eulerFunction(T1 value, T1 MOD); // Euler function

   template <typename T1>
   T1 carmichaelFunction(T1 value, T1 MOD); // Carmichael function

   //////////////////////////////////////////////////////////////////////////////////////////////
   template <typename T1>
   bool isPrime(T1 value, T1 k); // Miller–Rabin primality test
}

#include "source/mod-num.tcc"