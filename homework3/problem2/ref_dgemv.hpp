#ifndef REF_DGEMV_HPP
#define REF_DGEMV_HPP

#include <vector>

// Computes y ← α A x + β y
void dgemv(double alpha,
           const std::vector<std::vector<double>>& A,
           const std::vector<double>& x,
           double beta,
           std::vector<double>& y);

#endif
