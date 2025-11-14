#include "refBLAS.hpp"

void dgemv(double a,
           const std::vector<std::vector<double>>& A,
           const std::vector<double>& x,
           double b,
           std::vector<double>& y) {
    for (size_t i = 0; i < A.size(); ++i) {
        double dot = 0;
        for (size_t j = 0; j < A[0].size(); ++j)
            dot += A[i][j] * x[j];
        y[i] = a * dot + b * y[i];
    }
}

void dgemm(double a,
           const std::vector<std::vector<double>>& A,
           const std::vector<std::vector<double>>& B,
           double b,
           std::vector<std::vector<double>>& C) {
    size_t n = A.size();
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < n; ++j) {
            double sum = 0;
            for (size_t k = 0; k < n; ++k)
                sum += A[i][k] * B[k][j];
            C[i][j] = a * sum + b * C[i][j];
        }
}
