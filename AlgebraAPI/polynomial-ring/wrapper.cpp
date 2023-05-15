#include <gmpxx.h>

#include <sstream>
#include <string>

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
        std::cout << b << std::endl;

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
extern "C" char **
polyAddition(size_t &retSize, size_t polySize1, char **polyStr1, size_t polySize2, char **polyStr2,
             char *numModStr, char *errorStr) {
    try {
        mpz_class numMod;
        numMod.set_str(numModStr, 10);

        Polynomial<mpz_class> poly1(stringToPolyVector(polyStr1, polySize1, numMod), numMod);
        Polynomial<mpz_class> poly2(stringToPolyVector(polyStr2, polySize2, numMod), numMod);

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
polyMultiplication(size_t &retSize, size_t polySize1, char **polyStr1, size_t polySize2,
                   char **polyStr2, char *numModStr, char *errorStr) {
    try {
        mpz_class numMod;
        numMod.set_str(numModStr, 10);

        Polynomial<mpz_class> poly1(stringToPolyVector(polyStr1, polySize1, numMod), numMod);
        Polynomial<mpz_class> poly2(stringToPolyVector(polyStr2, polySize2, numMod), numMod);

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

/*
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

int
main() {}