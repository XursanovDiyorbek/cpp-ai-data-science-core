# C++ matrix foundations

A small, tested C++17 implementation of dense matrix operations. This repository is a learning project for the linear algebra and software engineering foundations used in data science and AI. It is deliberately limited in scope; it is not a replacement for an optimized numerical library.

## Implemented

| Operation | Input | Cost |
| --- | --- | --- |
| Transpose | Any non-empty rectangular matrix | O(rows × columns) |
| Multiply | Matrices whose inner dimensions match | O(rows × inner × columns) |
| Primary and secondary diagonal sums | Non-empty square matrix | O(size) |

Each operation rejects empty matrices, zero-column matrices, ragged rows, and incompatible dimensions with `std::invalid_argument`. The functions are in the `foundations` namespace and accept `std::vector<std::vector<double>>`. Floating-point multiplication uses the ordinary accumulation order and is intended for learning, not high-performance workloads.

## Build and verify

Requires a C++17 compiler. From the repository root:

```sh
g++ -std=c++17 -Wall -Wextra -Wpedantic -Werror -Iinclude src/matrix.cpp tests/matrix_tests.cpp -o matrix_tests
./matrix_tests
```

On Windows PowerShell, run `./matrix_tests.exe` after compiling. The test program checks rectangular multiplication and transpose, single-element cases, diagonal sums, and invalid shapes. GitHub Actions runs the same checks on pushes and pull requests.

An optional example prints the product of a 2×3 and a 3×2 matrix:

```sh
g++ -std=c++17 -Wall -Wextra -Wpedantic -Iinclude src/matrix.cpp examples/matrix_demo.cpp -o matrix_demo
./matrix_demo
```

## Next steps

Future exercises may add a contiguous matrix representation and benchmarks against this nested-vector version. Those are planned work, not implemented features..

