#include <gtest/gtest.h>

#include "math/Projector.h"

TEST(ProjectorTest, ProjectsPointCorrectly) {
  Projector projector;
  const Vec3 point{2.0, 4.0, -8.0};
  constexpr double focalLength = 2.0;

  const Vec3 projected = projector.projectPoint(point, focalLength);

  EXPECT_DOUBLE_EQ(projected.x, 0.5);
  EXPECT_DOUBLE_EQ(projected.y, 1.0);
  EXPECT_DOUBLE_EQ(projected.z, -8.0);
}

TEST(ProjectorTest, HandlesZeroZ) {
  Projector projector;
  const Vec3 point{1.0, 1.0, 0.0};
  constexpr double focalLength = 2.0;

  const Vec3 projected = projector.projectPoint(point, focalLength);

  EXPECT_TRUE(std::isinf(projected.x) || std::isnan(projected.x));
  EXPECT_TRUE(std::isinf(projected.y) || std::isnan(projected.y));
  EXPECT_DOUBLE_EQ(projected.z, 0.0);
}