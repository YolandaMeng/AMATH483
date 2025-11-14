#include "ref_axpyt.hpp"
#include <iostream>
#include <vector>
#include <cmath>

#ifdef TEST_MAIN
int main() {
    std::vector<double> u{1.0, 2.0, -1.0, 0.5};
    std::vector<double> v{0.0, 1.0, 2.0, 3.0};
    double scale = 2.5;

    std::vector<double> expected_v = v;
    for (size_t i = 0; i < expected_v.size(); ++i) {
        expected_v[i] += scale * u[i];
    }

    axpy(scale, u, v);

    for (size_t i = 0; i < v.size(); ++i) {
        if (std::fabs(v[i] - expected_v[i]) > 1e-12) {
            std::cerr << "[FAIL] axpy<double> mismatch at i=" << i
                      << ": got " << v[i]
                      << ", expected " << expected_v[i] << "\n";
            return 1;
        }
    }

    std::cout << "[PASS] axpy<double> verified.\n";

    std::vector<int> a{1, 2, 3};
    std::vector<int> b{0, 1, 2};
    int alpha = 3;

    std::vector<int> expected_b = b;
    for (size_t i = 0; i < expected_b.size(); ++i) {
        expected_b[i] += alpha * a[i];
    }

    axpy(alpha, a, b);

    for (size_t i = 0; i < b.size(); ++i) {
        if (b[i] != expected_b[i]) {
            std::cerr << "[FAIL] axpy<int> mismatch at i=" << i << "\n";
            return 1;
        }
    }

    std::cout << "[PASS] axpy<int> verified.\n";
    return 0;
}
#endif
