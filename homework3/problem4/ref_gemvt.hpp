#ifndef REF_GEMVT_HPP
#define REF_GEMVT_HPP

#include <vector>
#include <stdexcept>

// GEMV: y ← a * A * x + b * y
template <typename T>
void gemv(T a,
          const std::vector<std::vector<T>>& A,
          const std::vector<T>& x,
          T b,
          std::vector<T>& y)
{
    size_t n = A.size();
    if (x.size() != n || y.size() != n)
        throw std::invalid_argument("gemv: dimensions must match A, x, and y");

    for (size_t i = 0; i < n; ++i) {
        T dot = 0;
        for (size_t j = 0; j < n; ++j) {
            dot += A[i][j] * x[j];
        }
        y[i] = a * dot + b * y[i];
    }
}

#endif
