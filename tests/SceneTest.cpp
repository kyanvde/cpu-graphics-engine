#include <gtest/gtest.h>

#include "model/Scene.h"

TEST(SceneTest, DefaultValues) {
  Scene scene;
  EXPECT_EQ(scene.getMaxImageSize(), 0);
  EXPECT_EQ(scene.getBackgroundColor(), Color{});
  EXPECT_EQ(scene.getCamera(), Vec3{});
  EXPECT_TRUE(scene.getObjects().empty());
}

TEST(SceneTest, SetMaxImageSize) {
  Scene scene;
  scene.setMaxImageSize(800);
  EXPECT_EQ(scene.getMaxImageSize(), 800);
}

TEST(SceneTest, SetBackgroundColor) {
  Scene scene;
  const Color color{255, 255, 255};
  scene.setBackgroundColor(color);
  EXPECT_EQ(scene.getBackgroundColor(), color);
}

TEST(SceneTest, SetCamera) {
  Scene scene;
  const Vec3 camera{0.0, 0.0, 5.0};
  scene.setCamera(camera);
  EXPECT_EQ(scene.getCamera(), camera);
}