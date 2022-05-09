//
// Created by vladimir on 02.04.2022.
//

#include "gtest/gtest.h"
#include "my_project/solvers/ConjugateGradient.hpp"

TEST(TestMethodCG, Test) {

    const int N = 100;
    std::vector<double> AnaliticSolve(N, 0.);
    std::vector<double> b(N, 0);
    std::vector<double> initialState(N, 1.);

    std::vector<double> values;
    for (int i = 100; i > 0 ; --i) {
        values.push_back(i);
    }
    std::vector<std::size_t> colums;
    std::vector<std::size_t> rows;
    for (std::size_t i = 0; i < 100; ++i) {
        colums.push_back(i);
        rows.push_back(i);
    }

    Slae::Matrix::CSR<double> TestMatrix(N, N, values, colums, rows);

    double tao = 10e-12;

    auto res = Slae::Solvers::ConjugateGradient(TestMatrix, b, tao, initialState);
    for (int i = 0; i < AnaliticSolve.size(); ++i) {
        EXPECT_EQ(AnaliticSolve[i], res[i])
                            << "Method CG gives another result than correct analitics resullt with this tao: "
                            << res[i] << " Analitics result: " << AnaliticSolve[i];
    }
}