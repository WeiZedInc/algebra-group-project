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
        std::cout << "int16_t" << std::endl;
        std::cout << std::to_string(std::numeric_limits<int16_t>::max()) << std::endl;

        return Short;
    }

    else if (compstr(num, std::to_string(std::numeric_limits<int32_t>::max()).c_str()) <= 0) {
        std::cout << "int32_t" << std::endl;
        std::cout << std::to_string(std::numeric_limits<int32_t>::max()) << std::endl;
        return Int;
    }

    else if (compstr(num, std::to_string(std::numeric_limits<int64_t>::max()).c_str()) <= 0) {
        std::cout << "int64_t" << std::endl;
        std::cout << std::to_string(std::numeric_limits<int64_t>::max()) << std::endl;
        return Long;
    }

    std::cout << std::to_string(std::numeric_limits<long long>::max()) << std::endl;
    return ExtraLong;
}

template <typename numT>
numT
additionNumerical(numT a, numT b, numT mod) {
    if (mod < 1) {
        std::invalid_argument("mod must be greater or equal 1");
    }

    modNum<numT> a1(a, mod), b1(b, mod);
    modNum<numT> c = a1 + b1;

    return c.getValue();
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
