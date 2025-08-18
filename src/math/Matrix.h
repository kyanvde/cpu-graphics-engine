#ifndef MATRIX_H
#define MATRIX_H

#include <array>
#include <cassert>
#include <initializer_list>
#include <type_traits>

#include "MathUtils.h"

// RxC matrix of type T
template <typename T, std::size_t R, std::size_t C>
struct Matrix {
  // stored as row-major
  std::array<std::array<T, C>, R> m{};

  // Constructors

  // zero-initialize
  constexpr Matrix() = default;

  // from (nested) initializer list
  constexpr Matrix(std::initializer_list<std::initializer_list<T>> init) {
    assert(init.size() <= R);
    auto rowIt = init.begin();
    for (std::size_t i = 0; i < init.size(); ++i, ++rowIt) {
      assert(rowIt->size() <= C);
      auto colIt = rowIt->begin();
      for (std::size_t j = 0; j < rowIt->size(); ++j, ++colIt) {
        m[i][j] = *colIt;
      }
    }
  }

  // identity
  template <std::size_t N = R, typename = std::enable_if_t<N == C>>
  static constexpr Matrix<T, N, N> identity() {
    Matrix<T, N, N> matrix;
    for (std::size_t i = 0; i < N; ++i) matrix.m[i][i] = T(1);
    return matrix;
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
  template <std::size_t K>
  constexpr Matrix<T, R, K> operator*(Matrix<T, C, K> const& other) const {
    Matrix<T, R, K> result;
    for (std::size_t i = 0; i < R; ++i) {
      for (std::size_t k = 0; k < K; ++k) {
        T sum = T(0);
        for (std::size_t j = 0; j < C; ++j) sum += m[i][j] * other.m[j][k];
        result.m[i][k] = sum;
      }
    }
    return result;
  }

  // Premade matrices
  static Matrix<float, 3, 3> scale(double scaleFactor) {
    Matrix scaleMatrix = identity<>();
    scaleMatrix.m[0][0] = scaleFactor;
    scaleMatrix.m[1][1] = scaleFactor;
    scaleMatrix.m[2][2] = scaleFactor;

    return scaleMatrix;
  }

  static Matrix<float, 3, 3> rotateX(const double angle) {
    const double radAngle = MathUtils::degToRad(angle);
    const double angleSin = std::sin(radAngle);
    const double angleCos = std::cos(radAngle);

    Matrix xRotateMatrix;
    xRotateMatrix(0, 0) = 1;
    xRotateMatrix(1, 1) = angleCos;
    xRotateMatrix(1, 2) = angleSin;
    xRotateMatrix(2, 1) = -angleSin;
    xRotateMatrix(2, 2) = angleCos;

    return xRotateMatrix;
  }

  static Matrix<float, 3, 3> rotateY(const double angle) {
    const double radAngle = MathUtils::degToRad(angle);
    const double angleSin = std::sin(radAngle);
    const double angleCos = std::cos(radAngle);

    Matrix yRotateMatrix;
    yRotateMatrix(0, 0) = angleCos;
    yRotateMatrix(0, 2) = angleSin;
    yRotateMatrix(1, 1) = 1;
    yRotateMatrix(2, 0) = -angleSin;
    yRotateMatrix(2, 2) = angleCos;

    return yRotateMatrix;
  }
};

#endif  // MATRIX_H
