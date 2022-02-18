//
// Created by vladimir on 05.02.2022.
//

#ifndef MY_PROJECT_THREEDIAGONALSOLVER_HPP
#define MY_PROJECT_THREEDIAGONALSOLVER_HPP

#include "my_project/matrix/ThreeDiagonalMatrix.hpp"
#include <sstream>
#include <vector>
#include <array>

namespace Slae::Solvers {
    std::vector<double> solveThreeDiagonal(const Matrix::ThreeDiagonalMatrix &matrix, const std::vector<double> &col);
} // namespace Slae::Solvers {

#endif //MY_PROJECT_THREEDIAGONALSOLVER_HPP
