#include <gtest/gtest.h>

#include "math/MathUtils.h"

TEST(MathUtilsTest, DegToRad) {
  EXPECT_DOUBLE_EQ(MathUtils::degToRad(0), 0);
  EXPECT_DOUBLE_EQ(MathUtils::degToRad(180), M_PI);
  EXPECT_DOUBLE_EQ(MathUtils::degToRad(360), 2 * M_PI);
  EXPECT_DOUBLE_EQ(MathUtils::degToRad(90), M_PI / 2);
}

TEST(MathUtilsTest, RadToDeg) {
  EXPECT_DOUBLE_EQ(MathUtils::radToDeg(0), 0);
  EXPECT_DOUBLE_EQ(MathUtils::radToDeg(M_PI), 180);
  EXPECT_DOUBLE_EQ(MathUtils::radToDeg(2 * M_PI), 360);
  EXPECT_DOUBLE_EQ(MathUtils::radToDeg(M_PI / 2), 90);
}