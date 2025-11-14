#include "ref_dgemv.hpp"
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <cmath>
#include <stdexcept>

void dgemv(double alpha,
           const std::vector<std::vector<double>>& A,
           const std::vector<double>& x,
           double beta,
           std::vector<double>& y)
{
    size_t n = A.size();
    if (x.size() != n || y.size() != n) {
        throw std::invalid_argument("Dimension mismatch.");
    }

    for (size_t i = 0; i < n; ++i) {
        double sum = 0.0;
        for (size_t j = 0; j < n; ++j) {
            sum += A[i][j] * x[j];
        }
        y[i] = alpha * sum + beta * y[i];
    }
}

#ifdef TEST_MAIN
int main()
{
    const int n_min = 2;
    const int n_max = 512;
    const int n_trials = 5;
    const double alpha = 2.1;
    const double beta  = 0.9;

    std::mt19937 rng(42);
    std::uniform_real_distribution<double> dist(-1.0, 1.0);
    std::ofstream csv("dgemv_perf.csv");
    csv << "n,GFLOPS\n";

    for (int n = n_min; n <= n_max; ++n) {
        std::vector<std::vector<double>> A(n, std::vector<double>(n));
        std::vector<double> x(n), y(n), y_orig(n);

        for (int i = 0; i < n; ++i) {
            x[i] = dist(rng);
            y[i] = dist(rng);
            y_orig[i] = y[i];
            for (int j = 0; j < n; ++j)
                A[i][j] = dist(rng);
        }

        {
            std::vector<double> y_ref = y_orig;
            dgemv(alpha, A, x, beta, y_ref);
            dgemv(alpha, A, x, beta, y_orig);
            for (int i = 0; i < n; ++i) {
                if (std::abs(y_ref[i] - y_orig[i]) > 1e-12) {
                    std::cerr << "Mismatch at n=" << n << ", index=" << i << "\n";
                    return 1;
                }
            }
        }

        dgemv(alpha, A, x, beta, y);

        double total_time = 0.0;
        for (int t = 0; t < n_trials; ++t) {
            for (int i = 0; i < n; ++i)
                y[i] = dist(rng);

            auto start = std::chrono::high_resolution_clock::now();
            dgemv(alpha, A, x, beta, y);
            auto end = std::chrono::high_resolution_clock::now();

            total_time += std::chrono::duration<double>(end - start).count();
        }

        double avg_time = total_time / n_trials;
        double gflops = (2.0 * n * n / avg_time) / 1e9;
        csv << n << "," << gflops << "\n";
    }

    std::cout << "Benchmark results saved to dgemv_perf.csv\n";
    return 0;
}
#endif
