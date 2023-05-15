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
             char *numModStr) {
    mpz_class numMod;
    numMod.set_str(numModStr, 10);

    Polynomial<mpz_class> poly1(stringToPolyVector(polyStr1, polySize1, numMod), numMod);
    Polynomial<mpz_class> poly2(stringToPolyVector(polyStr2, polySize2, numMod), numMod);

    Polynomial<mpz_class> polyRes = poly1 + poly2;
    polyRes.print();

    retSize = polyRes.size();

    char **resStr = polyVectorToString(polyRes.toPolyVector());

    return resStr;
}

extern "C" char **
polySubstruction(size_t &retSize, size_t polySize1, char **polyStr1, size_t polySize2,
                 char **polyStr2, char *numModStr) {
    mpz_class numMod;
    numMod.set_str(numModStr, 10);

    Polynomial<mpz_class> poly1(stringToPolyVector(polyStr1, polySize1, numMod), numMod);
    Polynomial<mpz_class> poly2(stringToPolyVector(polyStr2, polySize2, numMod), numMod);

    Polynomial<mpz_class> polyRes = poly1 - poly2;
    polyRes.print();

    retSize = polyRes.size();

    char **resStr = polyVectorToString(polyRes.toPolyVector());

    return resStr;
}

extern "C" char **
polyMultiplication(size_t &retSize, size_t polySize1, char **polyStr1, size_t polySize2,
                   char **polyStr2, char *numModStr) {
    mpz_class numMod;
    numMod.set_str(numModStr, 10);

    Polynomial<mpz_class> poly1(stringToPolyVector(polyStr1, polySize1, numMod), numMod);
    Polynomial<mpz_class> poly2(stringToPolyVector(polyStr2, polySize2, numMod), numMod);

    Polynomial<mpz_class> polyRes = poly1 * poly2;
    polyRes.print();

    retSize = polyRes.size();

    char **resStr = polyVectorToString(polyRes.toPolyVector());

    return resStr;
}
extern "C" char **
polyDivision(size_t &retSize, size_t polySize1, char **polyStr1, size_t polySize2, char **polyStr2,
             char *numModStr) {
    mpz_class numMod;
    numMod.set_str(numModStr, 10);

    Polynomial<mpz_class> poly1(stringToPolyVector(polyStr1, polySize1, numMod), numMod);
    Polynomial<mpz_class> poly2(stringToPolyVector(polyStr2, polySize2, numMod), numMod);

    Polynomial<mpz_class> polyRes = poly1 / poly2;
    polyRes.print();

    retSize = polyRes.size();

    char **resStr = polyVectorToString(polyRes.toPolyVector());

    return resStr;
}
extern "C" char **
polyRest(size_t &retSize, size_t polySize1, char **polyStr1, size_t polySize2, char **polyStr2,
         char *numModStr) {
    mpz_class numMod;
    numMod.set_str(numModStr, 10);

    Polynomial<mpz_class> poly1(stringToPolyVector(polyStr1, polySize1, numMod), numMod);
    Polynomial<mpz_class> poly2(stringToPolyVector(polyStr2, polySize2, numMod), numMod);

    Polynomial<mpz_class> polyRes = poly1 % poly2;
    polyRes.print();

    retSize = polyRes.size();

    char **resStr = polyVectorToString(polyRes.toPolyVector());

    return resStr;
}
