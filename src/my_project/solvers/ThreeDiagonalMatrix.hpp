//
// Created by vladimir on 05.02.2022.
//

#ifndef MY_PROJECT_THREEDIAGONALMATRIX_HPP
#define MY_PROJECT_THREEDIAGONALMATRIX_HPP

#include "my_project/SlaeBaseException.hpp"

#include <vector>
#include <array>
#include <sstream>
#include <string>

namespace Slae::Matrix {

    class ThreeDiagonalMatrix {
    std::vector<std::array<double, 3>> data_;

    public:
        explicit ThreeDiagonalMatrix(int size);
        static ThreeDiagonalMatrix Zero(int size);

        double &operator()(int i, int j);

        [[nodiscard]] const double &operator()(int i, int j) const;

        [[nodiscard]] unsigned int rows() const noexcept;
    };

} // namespace Slae::Matrix

#endif //MY_PROJECT_THREEDIAGONALMATRIX_HPP
