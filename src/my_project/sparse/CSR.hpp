//
// Created by petrov on 12.02.2022.
//

#ifndef SOLE2022_CSR_HPP
#define SOLE2022_CSR_HPP

#include <vector>
#include <iosfwd>
#include <set>

#include "../utility/triplet.hpp"

template<typename T>
class CSR {
public:
    using elm_t = T;          // Тип данных элементов матрицы
    using idx_t = std::size_t;// Тип индекса

private:
    const idx_t H, W;         //Размеры матрицы
    std::vector<elm_t> values;//Вектор значений (размер N - кол-во ненулевых элементов)
    std::vector<idx_t> cols;  // Вектор номеров столбцов, соответствующих значениям (размер N - кол-во ненулевых элементов)
    std::vector<idx_t> rows;  // Вектор индексации строк размера H+1, первый элемент = 0 в качестве запирающего

public:
    /***
     * Конструктор разреженной матрицы по готовым векторам с внутренней структурой
     * @param h число строк
     * @param w число столбцов
     * @param v вектор ненулевых значений
     * @param c вектор индексации столбцов
     * @param r вектор индексации строк
     */
    CSR(const idx_t &h, const idx_t &w, const std::vector<T>& v,const std::vector<T>& c, const std::vector<T>& r);

    /***
     * Конструктор разреженной матрицы по сету из Triplet
     * @param h число строк
     * @param w число столбцов
     */
    CSR(const idx_t &h, const idx_t &w, const std::set<Triplet<elm_t>>& in): H(h), W(w){
        values.resize(in.size());
        cols.resize(in.size());
        rows.resize(h + 1);
        int countInRow = 0;
        int currRow = 0;
        auto it = in.begin();
        for(idx_t k = 0; k < in.size(); ++k) {
            while(currRow < it->i) {
                rows[currRow + 1] = rows[currRow] + countInRow;
                ++currRow;
                countInRow = 0;
            }
            values[k] = it->value;
            cols[k] = it->j;
            ++countInRow;
            it = std::next(it);
        }
        for(++currRow; currRow <= H; ++currRow) {
            rows[currRow] = in.size();
        }
    }

    /***
     * Оператор получения элемента матрицы по индексам
     * @param i Номер строки
     * @param j Номер столбца
     * @return Значение элемента в позиции (i, j)
     */
    const elm_t &operator()(idx_t const i, idx_t const j) const {
        idx_t skip = this->rows[i];
        idx_t count = this->rows[i+1] - skip;
        for(idx_t k = skip; k < skip + count; ++k) {
            if(this->cols[k] == j) return this->values[k];
        }
        return static_cast<elm_t>(0);
    }

    /***
     * Оператор умножения матрицы на вектор
     * @param b Вектор, на который умножается матрица
     * @return Вектор - результат перемножения
     */
    std::vector<elm_t> operator*(const std::vector<elm_t> &b) const {
        std::vector<elm_t> res(this->H);
        for(idx_t i = 0; i < H; ++i) {
            idx_t skip = this->rows[i];
            idx_t count = this->rows[i+1] - skip;
            for(idx_t k = skip; k < skip + count; ++k) {
                res[i] += values[k] * b[cols[k]];
            }
        }
        return res;
    }
};

template<typename T>
std::ostream &operator<<(std::ostream &os, const CSR<T> &A);

#endif//SOLE2022_CSR_HPP
