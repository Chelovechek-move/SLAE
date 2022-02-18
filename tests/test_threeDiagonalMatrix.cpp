//
// Created by vladimir on 18.02.2022.
//

#include "gtest/gtest.h"
#include <my_project/SlaeBaseException.hpp>
#include <my_project/solvers/ThreeDiagonalSolver.hpp>

TEST(ThreeDiagonalMatrix, Test1) {

    int n = 3;
    Slae::Matrix::ThreeDiagonalMatrix Matrix1(n);
    Matrix1(0, 0) = 3.;
    Matrix1(0, 1) = 1.;
    Matrix1(1, 0) = 1.;
    Matrix1(1, 1) = 3.;
    Matrix1(1, 2) = 1.;
    Matrix1(2, 1) = 1.;
    Matrix1(2, 2) = 4.;

    std::vector<double> cols(n);
    cols[0] = 1.;
    cols[1] = 1.;
    cols[2] = 1.;

    std::vector<double> solutions(n);
    solutions[0] = 8. / 29;
    solutions[1] = 5. / 29;
    solutions[2] = 6. / 29;

    std::vector<double> result = Slae::Solvers::solveThreeDiagonal(Matrix1, cols);
    for (int i = 0; i < n; i++) {
        ASSERT_NEAR(result[i], solutions[i], 10e-10);
    }
    for (int i = 0; i < n; i++) {
        std::cout << result[i] << std::endl;
    }
}
