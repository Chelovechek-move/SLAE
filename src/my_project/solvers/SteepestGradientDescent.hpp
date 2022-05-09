//
// Created by vladimir on 19.03.2022.
//

#ifndef MY_PROJECT_STEEPESTGRADIENTDESCENT_HPP
#define MY_PROJECT_STEEPESTGRADIENTDESCENT_HPP
#include "my_project/sparse/CSR.hpp"
#include "my_project/utility/Norm.hpp"
#include "my_project/utility/Overloads.hpp"
#include <vector>

namespace Slae::Solvers {
    template<typename T>
    std::vector<T> SteepestGradientDescent(const Slae::Matrix::CSR<T> &A, const Slae::Matrix::CSR<T> &A_reverse, const std::vector<T> &b, T tolerance, const std::vector<T>& initialState) {
        if (A.rows_number() != b.size()) {
            std::stringstream buf;
            buf << "Matrix has unequal sizes! Matrix size: " << A.rows_number() << ". Col size: " << A.cols_number()
                << ".File:" << __FILE__ << ". Row: " << __LINE__;
            throw Slae::SlaeBaseExceptionCpp(buf.str());
        } else {
            std::vector<T> r = A * initialState - b;
            std::vector<T> currentState = initialState;
            std::cout << currentState << std::endl;
            T alpha = (r * r) / (r * (A * r));
            while (norm(r, NormType::ThirdNorm) > tolerance) {
                    currentState = currentState - alpha * r;
                    r = A * currentState - b;
                    alpha = (r * r) / (r * (A * r));
            }
            return currentState;
        }
    }
} //Slae::Solvers

#endif //MY_PROJECT_STEEPESTGRADIENTDESCENT_HPP
