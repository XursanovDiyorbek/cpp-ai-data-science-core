#include <iostream>
#include <vector>
#include <stdexcept>
#include <numeric>

/**
 * @file matrix_operations.cpp
 * @brief Core 2D Matrix Operations for Data Science & AI Foundations in C++
 * @date 2026-11-08
 */

using Matrix = std::vector<std::vector<double>>;

// Transpose an M x N matrix to N x M
Matrix transposeMatrix(const Matrix& A) {
    if (A.empty()) return {};
    size_t rows = A.size();
    size_t cols = A[0].size();
    Matrix result(cols, std::vector<double>(rows, 0.0));
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result[j][i] = A[i][j];
        }
    }
    return result;
}

// Calculate sum of main (primary) diagonal of N x N square matrix
double primaryDiagonalSum(const Matrix& A) {
    size_t n = A.size();
    double sum = 0.0;
    for (size_t i = 0; i < n; ++i) {
        sum += A[i][i];
    }
    return sum;
}

// Calculate sum of anti (secondary) diagonal of N x N square matrix
double secondaryDiagonalSum(const Matrix& A) {
    size_t n = A.size();
    double sum = 0.0;
    for (size_t i = 0; i < n; ++i) {
        sum += A[i][n - 1 - i];
    }
    return sum;
}

// Standard O(N^3) Matrix Multiplication: C = A * B
Matrix multiplyMatrices(const Matrix& A, const Matrix& B) {
    if (A.empty() || B.empty()) return {};
    size_t rowsA = A.size();
    size_t colsA = A[0].size();
    size_t rowsB = B.size();
    size_t colsB = B[0].size();

    if (colsA != rowsB) {
        throw std::invalid_argument("Matrix dimension mismatch for multiplication.");
    }

    Matrix C(rowsA, std::vector<double>(colsB, 0.0));
    for (size_t i = 0; i < rowsA; ++i) {
        for (size_t k = 0; k < colsA; ++k) {
            for (size_t j = 0; j < colsB; ++j) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

void printMatrix(const Matrix& mat) {
    for (const auto& row : mat) {
        for (double val : row) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
}

int main() {
    std::cout << "--- C++ Matrix Operations Verification ---\n";
    Matrix A = {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}
    };
    Matrix B = {
        {9.0, 8.0, 7.0},
        {6.0, 5.0, 4.0},
        {3.0, 2.0, 1.0}
    };

    std::cout << "Primary Diagonal Sum of A: " << primaryDiagonalSum(A) << "\n";
    std::cout << "Secondary Diagonal Sum of A: " << secondaryDiagonalSum(A) << "\n";

    Matrix T = transposeMatrix(A);
    std::cout << "Transposed A:\n";
    printMatrix(T);

    Matrix C = multiplyMatrices(A, B);
    std::cout << "A * B Multiplication Result (O(N^3)):\n";
    printMatrix(C);

    return 0;
}
