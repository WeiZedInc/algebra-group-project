// Function for extended Euclidean Algorithm
template<typename num> num gcdExtended(num a, num b, num *x, num *y)
{
    // Base Case
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }
    num x1, y1; // To store results of recursive call
    num gcd = gcdExtended(b % a, a, &x1, &y1);
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

template<typename num, typename T1, typename T2, typename T3>
T1 inv(T1 value1, T1 MOD)
{
    num x,y;

    num g = gcdExtended(value1, MOD, x, y);
    if (g != 1) {
        cout << "Euclid Algorithm: No solution!";
        return null;
    } else {
        x = (x % m + m) % m;
        cout << "Euclid Algorithm: " << x << endl;
        return x;
    }
}

/**
 *  @brief divides value1 by value2 in a modular field
 *  @param  value1 numerator
 *  @param  value2 denominator
 *  @param MOD  module
 *
 *
 *  complexity O(log(n))
 *  @return returns result of division
 */

template<typename num, typename T1, typename T2, typename T3, typename T4>
T1 div(T2 value1, T3 value2, T4 MOD)
{
    return value1 * inv(value2, MOD);
}
