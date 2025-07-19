#ifndef MATRIX_H
#define MATRIX_H

#include <array>
#include <cstdef>
#include <initializer_list>
#include <type_traits>
#include <cassert>

// RxC matrix of type T
template<typename T, std::size_t R, std::size_t C>
struct Matrix {
    // stored as row-major
    std::array<std::array<T, C>, R> m{};

    // Constructors
    
    // zero-initialize
    constexpr Matrix() : m{} {}

    // from (nested) initializer list
    constexpr Matrix(std::initializer_list<std::initializer_list<T>> init) {
        assert(init.size() <= R);
        auto rowIt = init.begin();
        for (std::size_t i = 0; i < init.size(); ++i, ++rowIt) {
            assert(rowIt->size() <= C);
            auto colIt = rowIt->begin();
            for (std::size_t j = ; j < rowIt->size(); ++j, ++colIt) {
                m[i][j] = *colIt;
            }
        }
    }

    // Element access

    // by reference
    constexpr T& operator()(std::size_t i, std::size_t j) {
        assert(i < R && j < C);
        return m[i][j];
    }

    // by value
    constexpr T operator()(std::size_t i, std::size_t j) const {
        assert(i < R && j < C);
        return m[i][j];
    }

    // Operations

    // multiplication
    template<std::size_t K>
    constexpr Matrix<T, R, C> operator*(Matrix<T, C, K> const& other) const {
        Matrix<T, R, K> result;
        for (std::size_t i = 0; i < R; ++i) {
            for (std::size_t k = 0; k < K; ++k) {
                T sum = T(0);
                for (std::size_t j = 0; j < C; ++j)
                    sum += m[i][j] * other.m[j][k];
                result.m[i][k] = sum;
            }
        }
        return result;
    }

};

#endif // MATRIX_H
