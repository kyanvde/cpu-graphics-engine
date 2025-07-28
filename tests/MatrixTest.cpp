#include <gtest/gtest.h>

#include "math/Matrix.h"

TEST(MatrixTest, DefaultConstructorZeroInitializes) {
  Matrix<int, 2, 3> m;
  for (std::size_t i = 0; i < 2; ++i)
    for (std::size_t j = 0; j < 3; ++j) EXPECT_EQ(m(i, j), 0);
}

TEST(MatrixTest, InitializerListConstructor) {
  Matrix<int, 2, 2> m{{{1, 2}, {3, 4}}};
  EXPECT_EQ(m(0, 0), 1);
  EXPECT_EQ(m(0, 1), 2);
  EXPECT_EQ(m(1, 0), 3);
  EXPECT_EQ(m(1, 1), 4);
}

TEST(MatrixTest, Identity) {
  auto id = Matrix<int, 3, 3>::identity();
  for (std::size_t i = 0; i < 3; ++i)
    for (std::size_t j = 0; j < 3; ++j) EXPECT_EQ(id(i, j), (i == j ? 1 : 0));
}

TEST(MatrixTest, Multiplication) {
  Matrix<int, 2, 3> a{{{1, 2, 3}, {4, 5, 6}}};
  Matrix<int, 3, 2> b{{{7, 8}, {9, 10}, {11, 12}}};
  auto c = a * b;
  EXPECT_EQ(c(0, 0), 58);
  EXPECT_EQ(c(0, 1), 64);
  EXPECT_EQ(c(1, 0), 139);
  EXPECT_EQ(c(1, 1), 154);
}
