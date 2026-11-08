#pragma once

#include <vector>

namespace foundations {

using Matrix = std::vector<std::vector<double>>;

// Operations accept non-empty, rectangular matrices with at least one column.
// Invalid shapes and incompatible dimensions throw std::invalid_argument.
Matrix transpose(const Matrix& matrix);
Matrix multiply(const Matrix& left, const Matrix& right);
double primary_diagonal_sum(const Matrix& matrix);
double secondary_diagonal_sum(const Matrix& matrix);

}  // namespace foundations
