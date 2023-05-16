#ifndef POLY_UTILS
#define POLY_UTILS
#include <string>

#include "../poly-ring-math.h"

template <class T>
std::string
Polynomial<T>::toString() const {
    // boolean used for adding the plus sign

    std::stringstream ss;
    bool first_number_checked = false;
    if (poly.empty()) {
        ss << "0";
    } else {
        for (auto it = poly.begin(); it != poly.end(); ++it) {
            if (first_number_checked) {
                ss << " + ";
            } else {
                first_number_checked = true;
            }
            if (it->deg() > 0) {
                if (it->k().getValue() > 1) {
                    ss << (it->k().getValue()) << "x^" << (it->deg());
                } else {
                    ss << "x^" << (it->deg());
                }
            } else {
                ss << (it->k().getValue());
            }
        }
    }
    ss << std::endl;
    return ss.str();
}

#endif