#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <iomanip>

std::vector<double> solveLinearSystem(std::vector<std::vector<double>> A, std::vector<double> b) {
    const size_t n = A.size();
    if (n == 0 || b.size() != n) {
        throw std::invalid_argument("Matrix and vector dimensions must match and be non-empty.");
    }
    for (const auto& row : A) {
        if (row.size() != n) {
            throw std::invalid_argument("Matrix A must be square.");
        }
    }

    for (size_t col = 0; col < n; ++col) {
        size_t pivotRow = col;
        double maxVal = std::abs(A[col][col]);
        for (size_t row = col + 1; row < n; ++row) {
            double val = std::abs(A[row][col]);
            if (val > maxVal) {
                maxVal = val;
                pivotRow = row;
            }
        }

        if (maxVal < 1e-12) {
            throw std::runtime_error("Matrix is singular or nearly singular.");
        }

        if (pivotRow != col) {
            std::swap(A[col], A[pivotRow]);
            std::swap(b[col], b[pivotRow]);
        }

        for (size_t row = col + 1; row < n; ++row) {
            double factor = A[row][col] / A[col][col];
            for (size_t k = col; k < n; ++k) {
                A[row][k] -= factor * A[col][k];
            }
            b[row] -= factor * b[col];
        }
    }

    std::vector<double> x(n, 0.0);
    for (int i = static_cast<int>(n) - 1; i >= 0; --i) {
        double sum = b[i];
        for (size_t j = static_cast<size_t>(i) + 1; j < n; ++j) {
            sum -= A[i][j] * x[j];
        }
        x[i] = sum / A[i][i];
    }

    return x;
}

int main() {
    std::vector<std::vector<double>> A = {
        {2.0, 1.0, -1.0},
        {-3.0, -1.0, 2.0},
        {-2.0, 1.0, 2.0}
    };
    std::vector<double> b = {8.0, -11.0, -3.0};

    try {
        std::vector<double> x = solveLinearSystem(A, b);
        std::cout << std::fixed << std::setprecision(4);
        std::cout << "Solution x: [";
        for (size_t i = 0; i < x.size(); ++i) {
            std::cout << x[i] << (i + 1 < x.size() ? ", " : "");
        }
        std::cout << "]" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
