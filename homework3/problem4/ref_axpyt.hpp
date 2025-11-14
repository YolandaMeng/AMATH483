#ifndef REF_AXPYT_HPP
#define REF_AXPYT_HPP

#include <vector>
#include <stdexcept>

template <typename T>
void axpy(T a, const std::vector<T>& x, std::vector<T>& y) {
    if (x.size() != y.size())
        throw std::invalid_argument("axpy: x and y must have same length");
    size_t n = x.size();
    for (size_t i = 0; i < n; ++i) {
        y[i] += a * x[i];
    }
}

#endif