//
// Created by vladimir on 30.03.2022.
//

#ifndef MY_PROJECT_SOR_HPP
#define MY_PROJECT_SOR_HPP

#include "../sparse/CSR.hpp"
#include "../utility/Norm.hpp"
#include "../utility/Overloads.hpp"

namespace Slae::Solvers {
    template<typename T>
    std::vector<T> SuccessiveOverRelaxation(const Slae::Matrix::CSR<T> &A, const std::vector<T> &b, const std::vector<T> &initialState,
                               const T &tolerance) {
        double w = 0.8;
        if (A.rows_number() != b.size()) {
            std::stringstream buf;
            buf << "Matrix has unequal sizes! Matrix size: " << A.rows_number() << ". Col size: " << A.cols_number()
                << ".File:" << __FILE__ << ". Row: " << __LINE__;
            throw SlaeBaseExceptionCpp(buf.str());
        } else {
            std::vector<T> r = A * initialState - b;
            std::vector<T> currentState = initialState;
            T sum;
            while (norm(r, NormType::ThirdNorm) > tolerance) {
                for (int i = 0; i < A.rows_number(); ++i) {
                    sum = static_cast<T>(0);
                    for (int k = 0; k < A.rows_number(); ++k) {
                        if (k != i) sum += A(i, k) * currentState[k];
                    }
                    currentState[i] = (1 - w) * currentState[i] + w * (b[i] - sum) / A(i, i);
                }
//                std::cout << norm(r, NormType::ThirdNorm) << std::endl;
                r = A * currentState - b;
            }
            return currentState;
        }
    }
} //Slae::Solvers

#endif //MY_PROJECT_SOR_HPP
