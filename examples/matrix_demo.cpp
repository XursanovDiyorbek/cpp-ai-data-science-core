#include "matrix.hpp"

#include <iostream>

int main() {
    const foundations::Matrix left{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
    const foundations::Matrix right{{7.0, 8.0}, {9.0, 10.0}, {11.0, 12.0}};
    const auto product = foundations::multiply(left, right);

    for (const auto& row : product) {
        for (const auto value : row) {
            std::cout << value << ' ';
        }
        std::cout << '\n';
    }
}
