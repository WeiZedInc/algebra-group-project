#ifndef CYCLATOMIC_TCC
#define CYCLATOMIC_TCC

#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <complex>
#include <cstdint>
#include <functional>
#include <iostream>
#include <numeric>
#include <sstream>
#include <unordered_map>
#include <vector>

#include "../poly-ring-math.h"

/**
 * Overloaded stream insertion operator for std::vector<T>.
 * Outputs the vector as a polynomial expression.
 *
 * @param os The output stream.
 * @param v The vector to be printed.
 * @return Reference to the output stream.
 */
template <typename T>
std::ostream &
operator<<(std::ostream &os, const std::vector<T> &v) {
    std::stringstream ss;
    if (!v.empty()) {
        for (int n = v.size() - 1; n >= 0; n--) {
            if (v.at(n) != 0) {
                if (n > 1) {
                    if (v.at(n) == 1) {
                        ss << " + ";
                    } else {
                        ss << " - ";
                    }
                    ss << "x^" << n;
                } else if (n == 1) {
                    if (v.at(n) > 0) {
                        ss << " + x";
                    } else {
                        ss << " - x";
                    }
                } else {
                    if (v.at(n) > 0) {
                        ss << " + 1";
                    } else {
                        ss << " - 1";
                    }
                }
            }
        }
        return os << ss.str();
    }
    return os;
}

/**
 * Subtracts two vectors representing polynomials.
 *
 * @param p The first polynomial vector.
 * @param q The second polynomial vector.
 * @return The result of subtracting p from q.
 */
template <typename T>
std::vector<T>
subtract(const std::vector<T> &p, const std::vector<T> &q) {
    std::vector<T> v(p);
    v.resize(std::max(p.size(), q.size()));

    for (size_t n = 0; n < q.size(); ++n) {
        v.at(q.size() - 1 - n) -= q.at(q.size() - 1 - n);
    }
    while (!v.empty() && v.back() == 0) {
        v.pop_back();
    }
    return v;
}

/**
 * Performs the Fast Fourier Transform (FFT) on a complex vector.
 *
 * @param v The complex vector to be transformed.
 * @param n The size of the vector.
 * @param k The recursion parameter (default = 1).
 * @return The transformed vector.
 */

std::vector<std::complex<long double>>
fft(const std::vector<std::complex<long double>> &v, int n, int k = 1) {
    if (abs(n) == abs(k)) {
        return {std::accumulate(v.begin(), v.end(), std::complex<long double>())};
    }
    std::array<std::vector<std::complex<long double>>, 2> u{};
    u.at(0).reserve(v.size() + 1);
    u.at(1).reserve(v.size() + 1);
    for (size_t i = 0; i < v.size(); ++i) {
        u.at(i % 2).push_back(v.at(i));
    }

    std::array<std::vector<std::complex<long double>>, 2> w{fft(u.at(0), n, k << 1),
                                                            fft(u.at(1), n, k << 1)};
    std::vector<std::complex<long double>> a;
    a.resize(abs(n / k));
    std::complex<long double> m;
    for (size_t i = 0, j = a.size() >> 1; i < j; ++i) {
        m = std::exp(std::complex<long double>(2 * M_PI * k * i / n) *
                     std::complex<long double>(0, 1));

        a.at(i) = a.at(i + j) = m * w.at(1).at(i);
        a.at(i) = w.at(0).at(i) + a.at(i);
        a.at(i + j) = w.at(0).at(i) - a.at(i + j);
    }
    return a;
}

/**
 * Multiplies two vectors representing polynomials using FFT (Fast Fourier Transform).
 *
 * @param p The first polynomial vector.
 * @param q The second polynomial vector.
 * @return The result of multiplying p by q.
 */
template <typename T>
std::vector<T>
multiply(const std::vector<T> &p, const std::vector<T> &q) {
    T n = 1 << static_cast<T>(log2(p.size() + q.size() - 2) + 1);

    std::vector<std::complex<long double>> a =
        fft(std::vector<std::complex<long double>>(p.begin(), p.end()), n);
    std::vector<std::complex<long double>> b =
        fft(std::vector<std::complex<long double>>(q.begin(), q.end()), n);
    std::vector<std::complex<long double>> c;
    std::vector<T> d;
    c.reserve(n);

    /* for (size_t i = 0; i < n; ++i) { c.push_back(a.at(i) * b.at(i)); } */
    std::transform(a.begin(), a.end(), b.begin(), std::back_inserter(c),
                   std::multiplies<std::complex<long double>>());
    for (const std::complex<long double> &m : fft(c, n, -1)) {
        d.push_back(static_cast<T>(round((m / std::complex<long double>(n)).real())));
    }
    while (!d.empty() && d.back() == 0) {
        d.pop_back();
    }
    return d;
}

/**
 * Multiplies two vectors representing polynomials using the FOIL method.
 *
 * @param p The first polynomial vector.
 * @param q The second polynomial vector.
 * @return The result of multiplying p by q.
 */
template <typename T>
std::vector<T>
multiply_foil(const std::vector<T> &p, const std::vector<T> &q) {
    /* this version of multiply uses the foil method */
    std::vector<T> v(p.size() + q.size(), 0);
    for (T n = 0; n < p.size(); ++n) {
        for (T m = 0; m < q.size(); ++m) {
            v.at(n + m) += p.at(n) * q.at(m);
        }
    }
    while (!v.empty() && v.back() == 0) {
        v.pop_back();
    }
    return v;
}

/**
 * Divides two vectors representing polynomials.
 *
 * @param p The dividend polynomial vector.
 * @param q The divisor polynomial vector.
 * @return The result of dividing p by q.
 */
template <typename T>
std::vector<T>
divide(std::vector<T> p, std::vector<T> q) {
    std::vector<T> terms(std::max(p.size(), q.size()) + 1, 0);
    while ((p.size() == q.size() && p.back() == q.back()) ||
           (p.size() > q.size() || p.back() > q.back())) {
        std::vector<T> term(p.size() - q.size() + 1, 0);

        term.at(term.size() - 1) = terms.at(term.size() - 1) = p.back() / q.back();

        p = subtract(p, (p.size() == q.size() ? multiply(q, term) : multiply_foil(q, term)));
        if (p.empty()) {
            break;
        }
    }
    while (!terms.empty() && terms.back() == 0) {
        terms.pop_back();
    }
    return terms;
}

/**
 * Computes the cyclotomic polynomial of order N.
 *
 * @param N The order of the cyclotomic polynomial.
 * @return The cyclotomic polynomial as a vector.
 */

template <typename T1, typename T2>
T1
GCD(T1 a, T2 b) {
    return GCD(a, static_cast<T1>(b));
}

template <typename T1>
T1
GCD(T1 a, T1 b) {
    if (a < b)
        return GCD(b, a);
    if (b == static_cast<T1>(0))
        return static_cast<T1>(a);

    return GCD(b, static_cast<T1>(a % b));
}

template <typename T>
vector<T>
getCyclotomicPolynomialRaw(T N) {
    static std::unordered_map<T, std::vector<T>> cache;
    if (N == 1) {
        return std::vector<T>({1, -1});
    }
    if (cache.count(N) > 0) {
        return cache.at(N);
    }
    std::function<bool(T)> prime = [](T p) -> bool {
        if (p <= 1) {
            return false;
        }
        if (p <= 3) {
            return true;
        }
        if (p % 2 == 0) {
            return false;
        }
        T m = static_cast<T>(sqrt(p)) + 1;
        for (T i = 3; i <= m; i += 2) {
            if (p % i == 0) {
                return false;
            }
        }
        return true;
    };

    std::function<bool(T, T)> power_of = [](T x, T p) -> bool {
        while (!(x % p) && x > 1) {
            x /= p;
        }
        return x == 1;
    };
    std::vector<T> v;
    if (prime(N)) {
        v.resize(N, 1);
    } else if ((N % 2 == 0) && ((N / 2) % 2 != 0) && prime(N / 2)) {
        T n = N / 2;
        v.reserve(n);
        for (T i = 0; i < n; ++i) {
            v.push_back((!(i % 2)) ? 1 : -1);
        }
    } else if (N > 1 && power_of(N, 2)) {
        v.resize(static_cast<size_t>(N / 2) + 1);
        v.at(0) = 1;
        v.at(v.size() - 1) = 1;
    } else if (((N % 12 == 0) && power_of(N / 12, 2)) || ((N % 18 == 0) && power_of(N / 18, 2))) {
        v.resize(static_cast<size_t>(N / 3) + 1);
        v.at(0) = 1;
        v.at(v.size() / 2) = -1;
        v.at(v.size() - 1) = 1;
    } else if (GCD(N, 9) == static_cast<T>(1) && power_of(N, 3)) {
        v.resize(static_cast<size_t>(N / 1.5) + 1);
        v.at(0) = 1;
        v.at(v.size() / 2) = 1;
        v.at(v.size() - 1) = 1;
    } else {
        std::vector<T> q = {1};

        // factors of N
        for (T i = 1, n = N / 2; i <= n; ++i) {
            if (N % i == 0) {
                std::vector<T> p = getCyclotomicPolynomialRaw(i);
                q = multiply(q, std::vector<T>(p.rbegin(), p.rend()));
            }
        }

        std::vector<T> p(static_cast<size_t>(N) + 1, 0);

        p.at(0) = -1;
        p.at(p.size() - 1) = 1;

        v = divide(p, q);
        std::reverse(v.begin(), v.end());
        cache.emplace(N, v);
    }
    return v;
}

/**
 * @brief Initializes the polynomial from the N-th cyclotomic polynomial modulo mod.
 *
 * This function initializes the polynomial from the N-th cyclotomic polynomial modulo mod.
 * The cyclotomic polynomial is first computed using the
 * getCyclotomicPolynomialRaw function, and then the coefficients
 * are added to the polynomial using the addNode function.
 *
 * @tparam T The type of the coefficients and modulus.
 * @param N The index of the cyclotomic polynomial to use.
 * @param mod The modulus to use for the coefficients.
 */
template <typename T>
void
Polynomial<T>::fromCyclotomic(T N, T mod) {
    vector<T> v;
    this->numMod = mod;
    if (N == 1) {
        v = std::vector<T>({1, -1});
    } else {
        v = getCyclotomicPolynomialRaw(N);
    }

    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i] << ' ' << i << std::endl;
        this->addNode(v[i], i);
    }
}

#endif