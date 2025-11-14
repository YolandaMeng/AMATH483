#include "ref_gemmt.hpp"
#include <iostream>
#include <vector>
#include <cmath>

#ifdef TEST_MAIN
int main() {
    const int n = 2;
    std::vector<std::vector<float>> A = {
        {1.0f, 2.0f},
        {0.0f, -1.0f}
    };

    std::vector<std::vector<float>> B = {
        {2.0f, -1.0f},
        {1.5f, 3.0f}
    };

    std::vector<std::vector<float>> C = {
        {1.0f, 0.0f},
        {2.0f, -2.0f}
    };

    std::vector<std::vector<float>> expected = C;

    float alpha = 1.2f;
    float beta = 0.5f;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            float sum = 0.0f;
            for (int k = 0; k < n; ++k)
                sum += A[i][k] * B[k][j];
            expected[i][j] = alpha * sum + beta * expected[i][j];
        }

    gemm(alpha, A, B, beta, C);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (std::abs(C[i][j] - expected[i][j]) > 1e-6f) {
                std::cerr << "[FAIL] gemm<float> mismatch at (" << i << ", " << j << ")\n";
                return 1;
            }

    std::cout << "[PASS] gemm<float> verified.\n";
    return 0;
}
#endif
