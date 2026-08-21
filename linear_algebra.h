#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H

#include <vector>

using Matrix = std::vector<std::vector<double>>;
using Vector = std::vector<double>;

Vector multiply(const Matrix& matrix, const Vector& vector);
Matrix multiply(const Matrix& a, const Matrix& b);
Matrix transpose(const Matrix& matrix);
double dot(const Vector& a, const Vector& b);
double l1Distance(const Vector& a, const Vector& b);
Vector normalizeProbability(Vector vector);
Vector powerIteration(
    const Matrix& transitionMatrix,
    Vector initialDistribution,
    int maxIterations = 10000,
    double tolerance = 1e-12
);

#endif
