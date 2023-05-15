#include "poly-basic.tcc"

#ifndef ADDITIONAL_CONSTRUCTORS_TCC
#define ADDITIONAL_CONSTRUCTORS_TCC
template <class T>
bool
cmp(const std::pair<T, size_t>& one, const std::pair<T, size_t>& two) {
    return one.second < two.second;
}

template <class T>
Polynomial<T>::Polynomial(std::vector<std::pair<T, size_t>> nodes, T mod) {
    this->numMod = mod;

    sort(nodes.begin(), nodes.end(),
         [](const auto& lhs, const auto& rhs) { return lhs.second > rhs.second; });

    for (auto valDegreePair : nodes) {
        poly.insert(poly.end(),
                    Node<T>(modNum<T>(valDegreePair.first, numMod), valDegreePair.second));
    }

    this->print();
}
#endif

int
main() {
    std::vector<std::pair<int, size_t>> nodes = {{3, 3}, {4, 2}, {5, 1}, {6, 0}};

    Polynomial<int> p(nodes, 123);
}