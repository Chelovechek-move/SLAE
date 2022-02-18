//
// Created by vladimir on 05.02.2022.
//

#include "ThreeDiagonalMatrix.hpp"

namespace Slae::Matrix {

    ThreeDiagonalMatrix::ThreeDiagonalMatrix(int size) : data_(size) {}

    ThreeDiagonalMatrix ThreeDiagonalMatrix::Zero(int size) {
        ThreeDiagonalMatrix result(size);
        for (auto& string : result.data_) {
            string = {0., 0., 0.};
        }
        return result;
    }

    double &ThreeDiagonalMatrix::operator()(int i, int j) {
#ifndef NDEBUG
        if (i >= data_.size()) {
            std::stringstream buff;
            buff << "Индекс i превышает размер матрицы! Полученный индекс: " << i << ". Размер матрицы: " << data_.size() << ". Файл: " << __FILE__ << ". Строка: " << __LINE__;
            throw SlaeBaseExceptionCpp(buff.str());
        }
        if (j > 2) {
            std::stringstream buff;
            buff << "Индекс j должен пинадлежать {0, 1, 2}! Полученный индекс: " << j << ". Размер матрицы: " << data_.size() << ". Файл: " << __FILE__ << ". Строка: " << __LINE__;
            throw SlaeBaseExceptionCpp(buff.str());
        }
#endif NDEBUG
        return data_[i][j];
    }

    const double &ThreeDiagonalMatrix::operator()(int i, int j) const{
#ifndef NDEBUG
        if (i >= data_.size()) {
            std::stringstream buff;
            buff << "Индекс i превышает размер матрицы! Полученный индекс: " << i << ". Размер матрицы: " << data_.size() << ". Файл: " << __FILE__ << ". Строка: " << __LINE__;
            throw SlaeBaseExceptionCpp(buff.str());
        }
        if (j > 2) {
            std::stringstream buff;
            buff << "Индекс j должен пинадлежать {0, 1, 2}! Полученный индекс: " << j << ". Размер матрицы: " << data_.size() << ". Файл: " << __FILE__ << ". Строка: " << __LINE__;
            throw SlaeBaseExceptionCpp(buff.str());
        }
#endif NDEBUG
        return data_[i][j];
    }

    unsigned int ThreeDiagonalMatrix::rows() const noexcept {
        return (data_.size());
    }
}