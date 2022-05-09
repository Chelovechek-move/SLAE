//
// Created by petrov on 19.02.2022.
//

#ifndef SLAE_SIMPLEITERATION_HPP
#define SLAE_SIMPLEITERATION_HPP

#include "../sparse/CSR.hpp"
#include "../utility/Norm.hpp"
#include "../utility/Overloads.hpp"

namespace Slae::Solvers {
    template<typename T>
    std::vector<T> SimpleIteration(const Slae::Matrix::CSR<T> &A, const std::vector<T> &b, const T &tao) {
        if (A.rows_number() != b.size()) {
            std::stringstream buf;
            buf << "Matrix has unequal sizes! Matrix size: " << A.rows_number() << ". Col size: " << A.cols_number()
                << ".File:" << __FILE__ << ". Row: " << __LINE__;
            throw SlaeBaseExceptionCpp(buf.str());
        } else {
            std::vector<T> initialState;
            initialState.resize(A.rows_number(), static_cast<T>(0));
            std::vector<T> r = A * initialState - b;
            std::vector<T> currentState = initialState;
            while (norm(r, NormType::ThirdNorm) > tao) {
                currentState = currentState - tao * (A * currentState - b);
                r = A * currentState - b;
            }
            return currentState;
        }
    }
} //Slae::Solvers

#endif//SLAE_SIMPLEITERATION_HPP