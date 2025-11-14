#ifndef REF_GEMMT_HPP
#define REF_GEMMT_HPP

#include <vector>
#include <stdexcept>

// GEMM: C ← a * A * B + b * C
template <typename T>
void gemm(T a,
          const std::vector<std::vector<T>>& A,
          const std::vector<std::vector<T>>& B,
          T b,
          std::vector<std::vector<T>>& C)
{
    size_t n = A.size();
    if (B.size() != n || C.size() != n)
        throw std::invalid_argument("gemm: matrices must be square and of same size");

    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < n; ++j) {
            T sum = 0;
            for (size_t k = 0; k < n; ++k) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = a * sum + b * C[i][j];
        }
}

#endif
