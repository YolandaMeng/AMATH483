#ifndef REF_DGEMM_HPP
#define REF_DGEMM_HPP

#include <vector>

void dgemm(double alpha,
           const std::vector<std::vector<double>>& A,
           const std::vector<std::vector<double>>& B,
           double beta,
           std::vector<std::vector<double>>& C);

#endif
