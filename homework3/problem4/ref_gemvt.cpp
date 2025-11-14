#include "ref_gemvt.hpp"
#include <iostream>
#include <vector>
#include <cmath>

#ifdef TEST_MAIN
int main() {
    const int dim = 3;
    std::vector<std::vector<double>> mat = {
        {1.0, 2.0, 0.0},
        {-1.0, 0.5, 1.0},
        {2.0, -1.5, 3.0}
    };

    std::vector<double> vec = {1.0, -1.0, 0.5};
    std::vector<double> out = {0.0, 1.0, 2.0};

    double alpha = 1.5;
    double beta = 0.7;

    std::vector<double> ref_out = out;
    for (int i = 0; i < dim; ++i) {
        double dot = 0.0;
        for (int j = 0; j < dim; ++j) {
            dot += mat[i][j] * vec[j];
        }
        ref_out[i] = alpha * dot + beta * ref_out[i];
    }

    gemv(alpha, mat, vec, beta, out);

    for (int i = 0; i < dim; ++i) {
        if (std::abs(out[i] - ref_out[i]) > 1e-12) {
            std::cerr << "[FAIL] gemv<double> mismatch at row " << i << "\n";
            return 1;
        }
    }

    std::cout << "[PASS] gemv<double> verified.\n";
    return 0;
}
#endif
