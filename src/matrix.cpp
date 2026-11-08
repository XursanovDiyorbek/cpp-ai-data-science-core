#include "matrix.hpp"

#include <cstddef>
#include <stdexcept>

namespace foundations {
namespace {

struct Shape {
    std::size_t rows;
    std::size_t columns;
};

Shape shape_of(const Matrix& matrix) {
    if (matrix.empty() || matrix.front().empty()) {
        throw std::invalid_argument("matrix must have at least one row and column");
    }

    const auto columns = matrix.front().size();
    for (const auto& row : matrix) {
        if (row.size() != columns) {
            throw std::invalid_argument("matrix rows must have equal length");
        }
    }
    return {matrix.size(), columns};
}

Shape square_shape_of(const Matrix& matrix) {
    const auto shape = shape_of(matrix);
    if (shape.rows != shape.columns) {
        throw std::invalid_argument("diagonal sum requires a square matrix");
    }
    return shape;
}

}  // namespace

Matrix transpose(const Matrix& matrix) {
    const auto shape = shape_of(matrix);
    Matrix result(shape.columns, std::vector<double>(shape.rows));
    for (std::size_t row = 0; row < shape.rows; ++row) {
        for (std::size_t column = 0; column < shape.columns; ++column) {
            result[column][row] = matrix[row][column];
        }
    }
    return result;
}

Matrix multiply(const Matrix& left, const Matrix& right) {
    const auto left_shape = shape_of(left);
    const auto right_shape = shape_of(right);
    if (left_shape.columns != right_shape.rows) {
        throw std::invalid_argument("matrix dimensions are incompatible for multiplication");
    }

    Matrix result(left_shape.rows, std::vector<double>(right_shape.columns));
    for (std::size_t row = 0; row < left_shape.rows; ++row) {
        for (std::size_t inner = 0; inner < left_shape.columns; ++inner) {
            for (std::size_t column = 0; column < right_shape.columns; ++column) {
                result[row][column] += left[row][inner] * right[inner][column];
            }
        }
    }
    return result;
}

double primary_diagonal_sum(const Matrix& matrix) {
    const auto shape = square_shape_of(matrix);
    double result = 0.0;
    for (std::size_t index = 0; index < shape.rows; ++index) {
        result += matrix[index][index];
    }
    return result;
}

double secondary_diagonal_sum(const Matrix& matrix) {
    const auto shape = square_shape_of(matrix);
    double result = 0.0;
    for (std::size_t index = 0; index < shape.rows; ++index) {
        result += matrix[index][shape.columns - index - 1];
    }
    return result;
}

}  // namespace foundations
