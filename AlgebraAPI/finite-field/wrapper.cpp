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
enum Type { Short, Int, Long, LongLong, ExtraLong };

int32_t
compstr(const char *a, const char *b) {
    if (strlen(a) > strlen(b))
        return 1;
    if (strlen(a) < strlen(b))
        return -1;
    return strcmp(a, b);
}

Type
determineType(char *num) {
    std::to_string(std::numeric_limits<int16_t>::max()).c_str();
    std::to_string(std::numeric_limits<int32_t>::max()).c_str();
    std::to_string(std::numeric_limits<long>::max()).c_str();
    std::to_string(std::numeric_limits<long long>::max()).c_str();

    if (compstr(num, std::to_string(std::numeric_limits<int16_t>::max()).c_str()) <= 0) {
        // std::cout << "int16_t" << std::endl;
        // std::cout << std::to_string(std::numeric_limits<int16_t>::max()) << std::endl;

        return Short;
    }

    else if (compstr(num, std::to_string(std::numeric_limits<int32_t>::max()).c_str()) <= 0) {
        // std::cout << "int32_t" << std::endl;
        // std::cout << std::to_string(std::numeric_limits<int32_t>::max()) << std::endl;
        return Int;
    }

    else if (compstr(num, std::to_string(std::numeric_limits<int64_t>::max()).c_str()) <= 0) {
        // std::cout << "int64_t" << std::endl;
        // std::cout << std::to_string(std::numeric_limits<int64_t>::max()) << std::endl;
        return Long;
    }

    // std::cout << std::to_string(std::numeric_limits<long long>::max()) << std::endl;
    return ExtraLong;
}

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
T
giveMaxType(T t) {
    return t;
}

template <typename T, typename... Args>
T
giveMaxType(T t, Args... args) {
    return std::max(t, giveMaxType(args...));
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

    return number;
}

template <typename Func>
char *
apply(Type T, char *a, char *b, char *c, Func func) {
    char ansString = new char[MESSAGE_LEN];
    switch (T) {
        case Short:
            int16_t ansShort, numA, numB, numC;
            func(ansShort, stringToNum<int16_t>(a), stringToNum<int16_t>(b),
                 stringToNum<int16_t>(c));

            stringToNum(numA, a);
            stringToNum(numB, b);
            stringToNum(numC, c);
            func(ansLongn numA, numB, numC);
            strcpy(ansString, std::to_string(int16_t ansShort).c_str());
            break;

        case Int:
            int32_t ansInt, numA, numB, numC;

            stringToNum(numA, a);
            stringToNum(numB, b);
            stringToNum(numC, c);
            func(ansInt, numA, numB, numC);
            strcpy(ansString, std::to_string(ansInt).c_str());
            break;

        case Long:
            int64_t ansLong, numA, numB, numC;
            stringToNum(numA, a);
            stringToNum(numB, b);
            stringToNum(numC, c);
            func(ansLongn numA, numB, numC);
            strcpy(ansString, std::to_string(ansLong).c_str());
            break;
    }

    return ansString;
}

char *
addition(char *a, char *b, char *mod) {
    Type maxT = std::max(determineType(a), determineType(b));
    return apply<int64_t>(maxT, a, b, mod, additionNumerical);
}
// Compile: g++ wrapper.cpp -lgmpxx -lgmp
//
int
main() {
    char a[] = "123";
    char b[] = "22";
    char c[] = "7";

    addition(a, b, c);
}
