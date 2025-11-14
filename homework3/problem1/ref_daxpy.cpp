#include "ref_daxpy.hpp"
#include <vector>
#include <cmath>
void daxpy(double alpha,
           const std::vector<double>& x,
           std::vector<double>& y)
{
    size_t len = x.size();
    for (size_t i = 0; i < len; ++i) {
        y[i] += alpha * x[i];
    }
}

#ifdef TEST_MAIN
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>

int main()
{
    const int min_size = 2;
    const int max_size = 512;
    const int num_trials = 5;
    const double scalar = 2.3;

    std::mt19937_64 engine(2025);
    std::uniform_real_distribution<double> uniform(0.0, 1.0);
    std::ofstream fout("daxpy_gflops.csv");
    fout << "vector_size,GFLOPS\n";

    for (int size = min_size; size <= max_size; ++size) {
        std::vector<double> x(size), y(size);
        for (int i = 0; i < size; ++i) {
            x[i] = uniform(engine);
            y[i] = uniform(engine);
        }

        {
            std::vector<double> y_check = y;
            for (int i = 0; i < size; ++i) {
                y_check[i] += scalar * x[i];
            }

            daxpy(scalar, x, y);

            for (int i = 0; i < size; ++i) {
                if (std::abs(y[i] - y_check[i]) > 1e-12) {
                    std::cerr << "Mismatch at n=" << size << ", i=" << i << "\n";
                    return 1;
                }
            }

            for (int i = 0; i < size; ++i) {
                y[i] = uniform(engine);
            }
        }

        double total_seconds = 0.0;
        for (int rep = 0; rep < num_trials; ++rep) {
            auto start = std::chrono::high_resolution_clock::now();
            daxpy(scalar, x, y);
            auto end = std::chrono::high_resolution_clock::now();
            total_seconds += std::chrono::duration<double>(end - start).count();
        }

        double avg_time = total_seconds / num_trials;
        double gflops = (2.0 * size / avg_time) / 1e9;

        fout << size << "," << gflops << "\n";
    }

    std::cout << "Results saved to daxpy_gflops.csv\n";
    return 0;
}
#endif
