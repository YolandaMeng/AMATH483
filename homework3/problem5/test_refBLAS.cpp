#include "refBLAS.hpp"
#include <iostream>
#include <vector>

int main() {
    // -------- Test AXPY --------
    std::vector<double> x{1.0, 2.0, 3.0};
    std::vector<double> y{4.0, 5.0, 6.0};
    axpy(2.0, x, y);  // y ← 2x + y
    std::cout << "AXPY result: ";
    for (double v : y) std::cout << v << " ";
    std::cout << "\n";

    // -------- Test GEMV --------
    std::vector<std::vector<double>> A = {
        {1.0, 2.0},
        {3.0, 4.0}
    };
    std::vector<double> xv{1.0, 1.0};
    std::vector<double> yv{0.0, 0.0};
    dgemv(1.0, A, xv, 0.0, yv);  // y ← Ax
    std::cout << "GEMV result: ";
    for (double v : yv) std::cout << v << " ";
    std::cout << "\n";

    // -------- Test GEMM --------
    std::vector<std::vector<double>> B = {
        {5.0, 6.0},
        {7.0, 8.0}
    };
    std::vector<std::vector<double>> C(2, std::vector<double>(2, 0.0));
    dgemm(1.0, A, B, 0.0, C);  // C ← AB
    std::cout << "GEMM result:\n";
    for (const auto& row : C) {
        for (double val : row)
            std::cout << val << " ";
        std::cout << "\n";
    }

    return 0;
}
