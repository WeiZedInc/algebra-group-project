#include <gmpxx.h>

#include <algorithm>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "poly-ring-math.h"

const size_t MESSAGE_LEN = 200;

vector<std::pair<mpz_class, size_t>>
stringToPolyVector(char **polyString, size_t polySize, mpz_class numMod) {
    vector<std::pair<mpz_class, size_t>> polyV(polySize);

    for (size_t i = 0; i < polySize; ++i) {
        mpz_class a;
        a.set_str(polyString[i * 2], 10);

        std::string s(polyString[i * 2 + 1]);
        std::stringstream sstream(s);
        size_t b;
        sstream >> b;

        polyV[i] = make_pair(a, b);
    }

    return polyV;
}

char **
polyVectorToString(vector<std::pair<mpz_class, size_t>> polyV) {
    char **resStr = new char *[polyV.size() * 2];

    for (size_t i = 0; i < polyV.size(); ++i) {
        resStr[i * 2] = new char[MESSAGE_LEN];
        strcpy(resStr[i * 2], polyV[i].first.get_str().c_str());

        resStr[i * 2 + 1] = new char[MESSAGE_LEN];
        strcpy(resStr[i * 2 + 1], std::to_string(polyV[i].second).c_str());
    }

    return resStr;
}

std::string
removeSpaces(std::string str) {
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

std::vector<std::pair<std::string, std::string>>
convertPolynomial(std::string polynomial) {
    polynomial = removeSpaces(polynomial);
    std::vector<std::pair<std::string, std::string>> result;
    std::stringstream ss(polynomial);
    std::string term;
    while (std::getline(ss, term, '+')) {
        int32_t pos = term.find("x");
        std::string coeff, degree;

        if (pos != -1) {
            coeff = term.substr(0, term.find("x"));
            degree = term.substr(term.find("^") + 1, term.size() - 1);
        }

        else {
            coeff = term;
            degree = "0";
        }
        result.push_back({coeff, degree});
    }
    return result;
}

extern "C" char **
polyParse(size_t &polySize, char *polyString) {
    std::vector<std::pair<std::string, std::string>> v = convertPolynomial(polyString);
    char **resStr = new char *[v.size() * 2];
    polySize = v.size();
    for (size_t i = 0; i < v.size(); ++i) {
        resStr[i * 2] = new char[v[i].first.size() + 1];
        resStr[i * 2 + 1] = new char[v[i].second.size() + 1];

        strcpy(resStr[i * 2], v[i].first.c_str());
        strcpy(resStr[i * 2 + 1], v[i].second.c_str());
    }
    return resStr;
}

extern "C" char **
polyAddition(size_t &retSize, size_t polySize1, char **polyStr1, size_t polySize2, char **polyStr2,
             char *numModStr, char *errorStr) {
    try {
        mpz_class numMod;
        numMod.set_str(numModStr, 10);

        Polynomial<mpz_class> poly1(stringToPolyVector(polyStr1, polySize1, numMod), numMod);
        Polynomial<mpz_class> poly2(stringToPolyVector(polyStr2, polySize2, numMod), numMod);

        poly1.print();
        poly2.print();

        Polynomial<mpz_class> polyRes = poly1 + poly2;

        polyRes.print();

        retSize = polyRes.size();

        char **resStr = polyVectorToString(polyRes.toPolyVector());

        return resStr;
    } catch (const std::exception &e) {
        strcpy(errorStr, e.what());
        return nullptr;
    }
}

extern "C" char **
polySubstruction(size_t &retSize, size_t polySize1, char **polyStr1, size_t polySize2,
                 char **polyStr2, char *numModStr, char *errorStr) {
    try {
        mpz_class numMod;
        numMod.set_str(numModStr, 10);

        Polynomial<mpz_class> poly1(stringToPolyVector(polyStr1, polySize1, numMod), numMod);
        Polynomial<mpz_class> poly2(stringToPolyVector(polyStr2, polySize2, numMod), numMod);

        Polynomial<mpz_class> polyRes = poly1 - poly2;

        retSize = polyRes.size();

        char **resStr = polyVectorToString(polyRes.toPolyVector());

        return resStr;
    } catch (const std::exception &e) {
        strcpy(errorStr, e.what());
        return nullptr;
    }
}

extern "C" char **
polyMultiplication(size_t &retSize, size_t polySize1, char **polyStr1, size_t polySize2,
                   char **polyStr2, char *numModStr, char *errorStr) {
    try {
        mpz_class numMod;
        numMod.set_str(numModStr, 10);

        Polynomial<mpz_class> poly1(stringToPolyVector(polyStr1, polySize1, numMod), numMod);
        Polynomial<mpz_class> poly2(stringToPolyVector(polyStr2, polySize2, numMod), numMod);

        poly1.print();
        poly2.print();

        Polynomial<mpz_class> polyRes = poly1 * poly2;
        polyRes.print();

        retSize = polyRes.size();

        char **resStr = polyVectorToString(polyRes.toPolyVector());

        return resStr;
    } catch (const std::exception &e) {
        strcpy(errorStr, e.what());
        return nullptr;
    }
}
extern "C" char **
polyDivision(size_t &retSize, size_t polySize1, char **polyStr1, size_t polySize2, char **polyStr2,
             char *numModStr, char *errorStr) {
    try {
        mpz_class numMod;
        numMod.set_str(numModStr, 10);

        Polynomial<mpz_class> poly1(stringToPolyVector(polyStr1, polySize1, numMod), numMod);
        Polynomial<mpz_class> poly2(stringToPolyVector(polyStr2, polySize2, numMod), numMod);

        Polynomial<mpz_class> polyRes = poly1 / poly2;
        polyRes.print();

        retSize = polyRes.size();

        char **resStr = polyVectorToString(polyRes.toPolyVector());

        return resStr;
    } catch (const std::exception &e) {
        strcpy(errorStr, e.what());
        return nullptr;
    }
}
extern "C" char **
polyRest(size_t &retSize, size_t polySize1, char **polyStr1, size_t polySize2, char **polyStr2,
         char *numModStr, char *errorStr) {
    try {
        mpz_class numMod;
        numMod.set_str(numModStr, 10);

        Polynomial<mpz_class> poly1(stringToPolyVector(polyStr1, polySize1, numMod), numMod);
        Polynomial<mpz_class> poly2(stringToPolyVector(polyStr2, polySize2, numMod), numMod);

        Polynomial<mpz_class> polyRes = poly1 % poly2;
        polyRes.print();

        retSize = polyRes.size();

        char **resStr = polyVectorToString(polyRes.toPolyVector());

        return resStr;
    } catch (const std::exception &e) {
        strcpy(errorStr, e.what());
        return nullptr;
    }
}
extern "C" char **
polyGCD(size_t &retSize, size_t polySize1, char **polyStr1, size_t polySize2, char **polyStr2,
        char *numModStr, char *errorStr) {
    try {
        mpz_class numMod;
        numMod.set_str(numModStr, 10);

        Polynomial<mpz_class> poly1(stringToPolyVector(polyStr1, polySize1, numMod), numMod);
        Polynomial<mpz_class> poly2(stringToPolyVector(polyStr2, polySize2, numMod), numMod);

        Polynomial<mpz_class> polyRes = poly1.gcd(poly2);

        retSize = polyRes.size();

        char **resStr = polyVectorToString(polyRes.toPolyVector());

        return resStr;
    } catch (const std::exception &e) {
        strcpy(errorStr, e.what());
        return nullptr;
    }
}

extern "C" char **
polyDerivative(size_t &retSize, size_t polySize1, char **polyStr1, char *numModStr,
               char *errorStr) {
    try {
        mpz_class numMod;
        numMod.set_str(numModStr, 10);

        Polynomial<mpz_class> poly1(stringToPolyVector(polyStr1, polySize1, numMod), numMod);

        Polynomial<mpz_class> polyRes = poly1.der();

        retSize = polyRes.size();

        char **resStr = polyVectorToString(polyRes.toPolyVector());

        return resStr;
    } catch (const std::exception &e) {
        strcpy(errorStr, e.what());
        return nullptr;
    }
}
/*
extern "C" char *
polyEvaluate(size_t polySize1, char **polyStr1, char *numModStr, char *evalPointStr,
             char *errorStr) {
    try {
        mpz_class numMod, evalPoint;

        evalPoint.set_str(evalPointStr, 10);

        numMod.set_str(numModStr, 10);

        Polynomial<mpz_class> poly1(stringToPolyVector(polyStr1, polySize1, numMod), numMod);

        mpz_class ret = poly1.evaluate(evalPoint).getValue();
        char *retStr = new char[MESSAGE_LEN];
        strcpy(retStr, ret.get_str().c_str());

        return retStr;
    } catch (const std::exception &e) {
        strcpy(errorStr, e.what());
        return nullptr;
    }
}

extern "C" char **
getCyclotomic(size_t &ret_size, char *orderStr, char *numModStr, char *errorStr) {
    try {
        mpz_class order, numMod;
        numMod.set_str(numModStr, .10);

        order.set_str(orderStr, 10);

        Polynomial<mpz_class> polyOrdered;
        polyOrdered.fromCyclotomic(order, numMod);

        char **resStr = polyVectorToString(polyOrdered.toPolyVector());

        return resStr;
    } catch (const std::exception &e) {
        strcpy(errorStr, e.what());
        return nullptr;
    }
}

*/

char **
getRandomPoly(int n) {
    char **poly = new char *[n * 2];
    for (int i = 0; i < n; ++i) {
        poly[i * 2] = new char[100];
        poly[i * 2 + 1] = new char[100];

        strcpy(poly[i * 2 + 1], std::to_string(n - i).c_str());
        strcpy(poly[i * 2], std::to_string(rand() % 10).c_str());
    }

    return poly;
}
