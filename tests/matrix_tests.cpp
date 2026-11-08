#include "matrix.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {

void require(bool condition, const std::string& message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

void require_close(double actual, double expected, const std::string& message) {
    require(std::abs(actual - expected) < 1e-12, message);
}

template <typename Operation>
void require_invalid_argument(Operation operation, const std::string& message) {
    try {
        operation();
    } catch (const std::invalid_argument&) {
        return;
    }
    throw std::runtime_error(message);
}

void test_transpose() {
    const foundations::Matrix input{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
    const foundations::Matrix expected{{1.0, 4.0}, {2.0, 5.0}, {3.0, 6.0}};
    require(foundations::transpose(input) == expected, "rectangular transpose");
    require(foundations::transpose({{7.0}}) == foundations::Matrix{{7.0}},
            "single-element transpose");
}

void test_multiply() {
    const foundations::Matrix left{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
    const foundations::Matrix right{{7.0, 8.0}, {9.0, 10.0}, {11.0, 12.0}};
    const foundations::Matrix expected{{58.0, 64.0}, {139.0, 154.0}};
    require(foundations::multiply(left, right) == expected, "rectangular multiplication");
    require(foundations::multiply({{2.5}}, {{4.0}}) == foundations::Matrix{{10.0}},
            "single-element multiplication");
}

void test_diagonals() {
    const foundations::Matrix input{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
    require_close(foundations::primary_diagonal_sum(input), 15.0, "primary diagonal");
    require_close(foundations::secondary_diagonal_sum(input), 15.0, "secondary diagonal");
    require_close(foundations::primary_diagonal_sum({{2.5}}), 2.5,
                  "single-element primary diagonal");
}

void test_invalid_shapes() {
    require_invalid_argument([] { foundations::transpose({}); }, "empty transpose must fail");
    require_invalid_argument([] { foundations::transpose({{}}); }, "zero columns must fail");
    require_invalid_argument([] { foundations::transpose({{1.0}, {2.0, 3.0}}); },
                             "ragged transpose must fail");
    require_invalid_argument([] { foundations::multiply({{1.0, 2.0}}, {{3.0}}); },
                             "incompatible multiplication must fail");
    require_invalid_argument([] { foundations::multiply({{1.0}, {2.0, 3.0}}, {{4.0}}); },
                             "ragged multiplication must fail");
    require_invalid_argument([] { foundations::primary_diagonal_sum({{1.0, 2.0}}); },
                             "non-square primary diagonal must fail");
    require_invalid_argument([] { foundations::secondary_diagonal_sum({{1.0}, {2.0}}); },
                             "non-square secondary diagonal must fail");
}

}  // namespace

int main() {
    try {
        test_transpose();
        test_multiply();
        test_diagonals();
        test_invalid_shapes();
        std::cout << "All matrix tests passed.\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "Matrix test failed: " << error.what() << '\n';
        return 1;
    }
}
