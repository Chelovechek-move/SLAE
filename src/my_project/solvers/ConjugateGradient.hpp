//
// Created by vladimir on 30.03.2022.
//

#ifndef MY_PROJECT_CONJUGATEGRADIENT_HPP
#define MY_PROJECT_CONJUGATEGRADIENT_HPP
#include "my_project/sparse/CSR.hpp"
#include "my_project/utility/Norm.hpp"
#include "my_project/utility/Overloads.hpp"
#include <vector>
#include <iostream>

namespace Slae::Solvers {
    template<typename T>
    std::vector<T> ConjugateGradient(const Slae::Matrix::CSR<T> &A, const std::vector<T> &b, T tao, const std::vector<T>& initialState) {
        auto r_prev = A * initialState - b;
        auto currentState = initialState;
        std::vector<T> eps;
        std::vector<int> counter;
        int count = 0;
        auto d = r_prev;
        auto r_next = r_prev;
        T alpha, beta;
        bool Go = (norm(r_prev, NormType::ThirdNorm) >= tao);
        eps.push_back(std::sqrt(currentState * (A * currentState)));
        counter.push_back(count);

        while (Go) {
            alpha = (r_prev * r_prev) / (d * (A * d));
            currentState = currentState - alpha * d;
            ++count;
            r_next = A * currentState - b;
            if (norm(r_next, NormType::ThirdNorm) < tao) {
                Go = false;
            } else {
                beta = (r_next * r_next) / (r_prev * r_prev);
                d = r_next + beta * d;
                Go = (norm(r_next, NormType::ThirdNorm) >= tao);
            }
            r_prev = r_next;
            eps.push_back(std::sqrt(currentState * (A * currentState)));
            counter.push_back(count);
        }
        std::cout << counter;
        std::cout << std::endl;
        std::cout << eps;
        return currentState;
    }
} //Slae::Solvers
#endif //MY_PROJECT_CONJUGATEGRADIENT_HPP
