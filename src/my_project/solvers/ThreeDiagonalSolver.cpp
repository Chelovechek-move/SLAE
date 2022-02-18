//
// Created by vladimir on 05.02.2022.
//

#include "ThreeDiagonalSolver.hpp"

namespace Slae::Solvers {
    std::vector<double> solveThreeDiagonal(const Matrix::ThreeDiagonalMatrix &matrix, const std::vector<double> &col) {

        if (matrix.rows() != col.size()) {
            std::stringstream buff;
            buff << "Размеры матрицы и столбца не совпадают! Размер матрицы: " << matrix.rows() << ". Размер столбца: " << col.size() << ". Файл: " << __FILE__ << ". Строка: " << __LINE__;
            throw SlaeBaseExceptionCpp(buff.str());
        }

        double gamma1 = (-1) * matrix(0, 1) / matrix(0, 0);
        double beta1 = col[0] / matrix(0, 0);

        int n = matrix.rows() - 1;
        std::vector<std::array<double, 2>> gammas_and_betas(n);
        gammas_and_betas[0][0] = gamma1;
        gammas_and_betas[0][1] = beta1;

        int shift = 0;
        for (int i = 1; i < n; i++) {
            gammas_and_betas[i][0] = (-1) * matrix(i, 2 + shift) /
                    (matrix(i, shift) * gammas_and_betas[i - 1][0] + matrix(i, 1 + shift));
            gammas_and_betas[i][1] = (col[i] - matrix(i, shift) * gammas_and_betas[i - 1][1]) /
                    (matrix(i, shift) * gammas_and_betas[i - 1][0] + matrix(i, 1 + shift));
            shift++;
        }

        std::vector<double> ans(matrix.rows());
        ans[n] =  (col[n] - matrix(n, n - 1) * gammas_and_betas[n - 1][1]) /
                (matrix(n, n - 1) * gammas_and_betas[n - 1][0] + matrix(n, n));

        for (int i = n - 1; i >= 0; i--) {
            ans[i] = gammas_and_betas[i][0] * ans[i + 1] + gammas_and_betas[i][1];
        }

        return ans;
    }
} // namespace Slae::Solvers {

