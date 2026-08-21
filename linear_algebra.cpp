#include "linear_algebra.h"
#include <cmath>
#include <numeric>

Vector multiply(const Matrix& matrix, const Vector& vector) {
    Vector result(matrix.size(), 0.0);

    for (int i = 0; i < static_cast<int>(matrix.size()); ++i) {
        for (int j = 0; j < static_cast<int>(vector.size()); ++j) {
            result[i] += matrix[i][j] * vector[j];
        }
    }

    return result;
}

Matrix multiply(const Matrix& a, const Matrix& b) {
    int rows = static_cast<int>(a.size());
    int inner = static_cast<int>(b.size());
    int columns = static_cast<int>(b[0].size());

    Matrix result(rows, Vector(columns, 0.0));

    for (int i = 0; i < rows; ++i) {
        for (int k = 0; k < inner; ++k) {
            for (int j = 0; j < columns; ++j) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return result;
}

Matrix transpose(const Matrix& matrix) {
    int rows = static_cast<int>(matrix.size());
    int columns = static_cast<int>(matrix[0].size());
    Matrix result(columns, Vector(rows, 0.0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            result[j][i] = matrix[i][j];
        }
    }

    return result;
}

double dot(const Vector& a, const Vector& b) {
    double result = 0.0;
    for (int i = 0; i < static_cast<int>(a.size()); ++i) {
        result += a[i] * b[i];
    }
    return result;
}

double l1Distance(const Vector& a, const Vector& b) {
    double distance = 0.0;
    for (int i = 0; i < static_cast<int>(a.size()); ++i) {
        distance += std::abs(a[i] - b[i]);
    }
    return distance;
}

Vector normalizeProbability(Vector vector) {
    double sum = std::accumulate(vector.begin(), vector.end(), 0.0);
    if (sum == 0.0) return vector;

    for (double& value : vector) {
        value /= sum;
    }
    return vector;
}

Vector powerIteration(
    const Matrix& transitionMatrix,
    Vector initialDistribution,
    int maxIterations,
    double tolerance
) {
    Matrix transposed = transpose(transitionMatrix);
    Vector current = normalizeProbability(initialDistribution);

    for (int iteration = 0; iteration < maxIterations; ++iteration) {
        Vector next = multiply(transposed, current);
        next = normalizeProbability(next);

        if (l1Distance(current, next) < tolerance) {
            return next;
        }
        current = next;
    }

    return current;
}
