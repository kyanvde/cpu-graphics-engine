#include <gtest/gtest.h>

#include "math/Vec3.h"

TEST(Vec3Test, DefaultConstructor) {
  constexpr Vec3 vector{};
  EXPECT_FLOAT_EQ(vector.x, 0);
  EXPECT_FLOAT_EQ(vector.y, 0);
  EXPECT_FLOAT_EQ(vector.z, 0);
}

TEST(Vec3Test, ParameterizedConstructor) {
  const Vec3 vector{1.0, 2.0, 3.0};
  EXPECT_FLOAT_EQ(vector.x, 1.0);
  EXPECT_FLOAT_EQ(vector.y, 2.0);
  EXPECT_FLOAT_EQ(vector.z, 3.0);
}

TEST(Vec3Test, EqualityOperator) {
  const Vec3 vector1{1.0, 2.0, 3.0};
  const Vec3 vector2{1.0, 2.0, 3.0};
  const Vec3 vector3{4.0, 5.0, 6.0};

  EXPECT_TRUE(vector1 == vector2);
  EXPECT_FALSE(vector1 == vector3);
}

TEST(Vec3Test, Addition) {
  const Vec3 vector1{1.0, 2.0, 3.0};
  const Vec3 vector2{4.0, 5.0, 6.0};
  const Vec3 result = vector1 + vector2;
  EXPECT_FLOAT_EQ(result.x, 5.0);
  EXPECT_FLOAT_EQ(result.y, 7.0);
  EXPECT_FLOAT_EQ(result.z, 9.0);

  const Vec3 vector3{-1.0, 2.0, 3.0};
  const Vec3 vector4{4.0, -5.0, -3.1};
  const Vec3 result2 = vector3 + vector4;
  EXPECT_FLOAT_EQ(result2.x, 3.0);
  EXPECT_FLOAT_EQ(result2.y, -3.0);
  EXPECT_FLOAT_EQ(result2.z, -0.1);
}

TEST(Vec3Test, Subtraction) {
  const Vec3 vector1{5.0, 7.0, 9.0};
  const Vec3 vector2{1.0, 2.0, 3.0};
  const Vec3 result = vector1 - vector2;
  EXPECT_FLOAT_EQ(result.x, 4.0);
  EXPECT_FLOAT_EQ(result.y, 5.0);
  EXPECT_FLOAT_EQ(result.z, 6.0);

  const Vec3 vector3{-1.0, 2.0, 3.0};
  const Vec3 vector4{4.0, -5.0, -3.1};
  const Vec3 result2 = vector3 - vector4;
  EXPECT_FLOAT_EQ(result2.x, -5.0);
  EXPECT_FLOAT_EQ(result2.y, 7.0);
  EXPECT_FLOAT_EQ(result2.z, 6.1);
}

TEST(Vec3Test, ScalarMultiplication) {
  const Vec3 vector{1.0, 2.0, 3.0};
  constexpr double scalar = 2.0;
  const Vec3 result = vector * scalar;
  EXPECT_FLOAT_EQ(result.x, 2.0);
  EXPECT_FLOAT_EQ(result.y, 4.0);
  EXPECT_FLOAT_EQ(result.z, 6.0);

  const Vec3 vector2{-1.0, 2.0, -3.0};
  constexpr double scalar2 = -1.5;
  const Vec3 result2 = vector2 * scalar2;
  EXPECT_FLOAT_EQ(result2.x, 1.5);
  EXPECT_FLOAT_EQ(result2.y, -3.0);
  EXPECT_FLOAT_EQ(result2.z, 4.5);
}

TEST(Vec3Test, VectorMultiplication) {
  const Vec3 vector1{1.0, 2.0, 3.0};
  const Vec3 vector2{4.0, 5.0, 6.0};
  const Vec3 result = vector1 * vector2;
  EXPECT_FLOAT_EQ(result.x, 4.0);
  EXPECT_FLOAT_EQ(result.y, 10.0);
  EXPECT_FLOAT_EQ(result.z, 18.0);

  const Vec3 vector3{-1.0, 2.0, -3.0};
  const Vec3 vector4{4.0, -5.0, -6.0};
  const Vec3 result2 = vector3 * vector4;
  EXPECT_FLOAT_EQ(result2.x, -4.0);
  EXPECT_FLOAT_EQ(result2.y, -10.0);
  EXPECT_FLOAT_EQ(result2.z, 18.0);
}

TEST(Vec3Test, CrossProduct) {
  const Vec3 vector1{1.0, 2.0, 3.0};
  const Vec3 vector2{4.0, 5.0, 6.0};
  const Vec3 result = vector1.cross(vector2);
  EXPECT_FLOAT_EQ(result.x, -3.0);
  EXPECT_FLOAT_EQ(result.y, 6.0);
  EXPECT_FLOAT_EQ(result.z, -3.0);

  const Vec3 vector3{-1.0, 2.0, -3.0};
  const Vec3 vector4{4.0, -5.0, -6.0};
  const Vec3 result2 = vector3.cross(vector4);
  EXPECT_FLOAT_EQ(result2.x, -27.0);
  EXPECT_FLOAT_EQ(result2.y, -18.0);
  EXPECT_FLOAT_EQ(result2.z, -3.0);
}

TEST(Vec3Test, Normalize) {
  const Vec3 vector{3.0, 4.0, 0.0};
  const Vec3 normalized = vector.normalize();
  EXPECT_FLOAT_EQ(normalized.x, 0.6);
  EXPECT_FLOAT_EQ(normalized.y, 0.8);
  EXPECT_FLOAT_EQ(normalized.z, 0.0);

  const Vec3 zeroVector{0.0, 0.0, 0.0};
  const Vec3 normalizedZero = zeroVector.normalize();
  EXPECT_FLOAT_EQ(normalizedZero.x, 0.0);
  EXPECT_FLOAT_EQ(normalizedZero.y, 0.0);
  EXPECT_FLOAT_EQ(normalizedZero.z, 0.0);
}
