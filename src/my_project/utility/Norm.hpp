//
// Created by petrov on 19.02.2022.
//

#ifndef SLAE_NORM_HPP
#define SLAE_NORM_HPP
#include <vector>
#include <cmath>

enum class NormType{
    FirstNorm = 1,
    SecondNorm = 2,
    ThirdNorm = 3,
};

template<typename T>
T norm(const std::vector<T>& vector, NormType normtype) {
    T norm = static_cast<T>(0);
    if(normtype == NormType::FirstNorm) {
        T abs;
        for(const auto& elm : vector) {
            abs = std::abs(elm);
            if(abs > norm) norm = abs;
        }
    }
    if(normtype == NormType::SecondNorm) {
        for(const auto& elm : vector) {
            norm += std::abs(elm);
        }
    }
    if(normtype == NormType::ThirdNorm) {
        for(const auto& elm : vector) {
            norm += elm * elm;
        }
        norm = std::sqrt(norm);
    }
    return norm;
}
#endif//SLAE_NORM_HPP
