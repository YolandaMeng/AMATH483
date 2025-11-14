#include "ref_dgemm.hpp"
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <cmath>
#include <stdexcept>

void dgemm(double alpha,
           const std::vector<std::vector<double>>& A,
           const std::vector<std::vector<double>>& B,
           double beta,
           std::vector<std::vector<double>>& C)
{
    size_t n = A.size();
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < n; ++j) {
            double sum = 0.0;
            for (size_t k = 0; k < n; ++k)
                sum += A[i][k] * B[k][j];
            C[i][j] = alpha * sum + beta * C[i][j];
        }
}

#ifdef TEST_MAIN
int main()
{
    const int n_min = 2;
    const int n_max = 512;
    const int n_trials = 5;
    const double alpha = 1.2;
    const double beta  = 0.8;

    std::mt19937_64 rng(483);
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    std::ofstream out("dgemm_perf.csv");
    out << "n,GFLOPS\n";

    for (int n = n_min; n <= n_max; ++n) {
        std::vector<std::vector<double>> A(n, std::vector<double>(n));
        std::vector<std::vector<double>> B(n, std::vector<double>(n));
        std::vector<std::vector<double>> C(n, std::vector<double>(n));
        std::vector<std::vector<double>> C_ref = C;

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                A[i][j] = dist(rng);
                B[i][j] = dist(rng);
                C[i][j] = dist(rng);
                C_ref[i][j] = C[i][j];
            }

        dgemm(alpha, A, B, beta, C);
        dgemm(alpha, A, B, beta, C_ref);

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (std::abs(C[i][j] - C_ref[i][j]) > 1e-12) {
                    std::cerr << "Mismatch at n=" << n << ", i=" << i << ", j=" << j << "\n";
                    return 1;
                }

        double total_time = 0.0;
        for (int trial = 0; trial < n_trials; ++trial) {
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    C[i][j] = dist(rng);

            auto start = std::chrono::high_resolution_clock::now();
            dgemm(alpha, A, B, beta, C);
            auto end = std::chrono::high_resolution_clock::now();

            total_time += std::chrono::duration<double>(end - start).count();
        }

        double avg_time = total_time / n_trials;
        double gflops = (2.0 * n * n * n / avg_time) / 1e9;
        out << n << "," << gflops << "\n";
    }

    std::cout << "Saved to dgemm_perf.csv\n";
    return 0;
}
#endif
