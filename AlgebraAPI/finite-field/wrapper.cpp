#include <gmpxx.h>
#include <string.h>

#include <algorithm>
#include <iostream>
#include <limits>
#include <stdexcept>

#include "mod-math.h"
#define EXPORT extern "C" __declspec(dllexport)

using namespace modular;

const size_t MESSAGE_LEN = 200;

template <typename numT>
void
additionNumerical(numT &ans, numT a, numT b, numT mod) {
    if (mod < 1) {
        std::invalid_argument("mod must be greater or equal 1");
    }

    modNum<numT> a1(a, mod), b1(b, mod);
    modNum<numT> c = a1 + b1;

    ans = c.getValue();
}

template <typename numT>
numT
subtractionNumerical(numT a, numT b, numT mod) {
    if (mod < 1) {
        std::invalid_argument("mod must be greater or equal 1");
    }

    modNum<numT> a1(a, mod), b1(b, mod);
    modNum<numT> c = a1 - b1;

    return c.getValue();
}

template <typename numT>
numT
multiplicationNumerical(numT a, numT b, numT mod) {
    if (mod < 1) {
        std::invalid_argument("mod must be greater or equal 1");
    }

    modNum<numT> a1(a, mod), b1(b, mod);
    modNum<numT> c = a1 * b1;

    return c.getValue();
}

template <typename numT>
numT
divisionNumerical(numT a, numT b, numT mod) {
    if (mod < 1) {
        std::invalid_argument("mod must be greater or equal 1");
    }

    modNum<numT> a1(a, mod), b1(b, mod);
    modNum<numT> c = a1 / b1;

    return c.getValue();
}

template <typename T>
void
stringToNum(T &number, char *s) {
    size_t len = strlen(s);

    number = 0;
    for (size_t i = 0; i < len; ++i) {
        number *= 10;
        number += s[i] - '0';
    }
}

char *
addition(char *a, char *b, char *mod) {
    mpz_class numA, numB, numC, ans;

    stringToNum(numA, a);
    stringToNum(numB, b);
    stringToNum(numC, mod);

    additionNumerical(ans, numA, numB, numC);

    char *ansStr = new char[MESSAGE_LEN];
    strcpy(ansStr, ans.get_str().c_str());

    return ansStr;
}
// Compile: g++ wrapper.cpp -lgmpxx -lgmp
//
int
main() {
    char a[] = "1";
    char b[] = "22";
    char c[] = "7";

    std::cout << addition(a, b, c) << std::endl;
}
