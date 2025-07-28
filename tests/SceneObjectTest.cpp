#include <gtest/gtest.h>

#include "model/Image.h"
#include "model/SceneObject.h"

class TestSceneObject final : public SceneObject {
 public:
  std::vector<Line> getProjectedLines() override { return {}; }
  void render(Image&) override {}
};

TEST(SceneObjectTest, SetAndGetColor) {
  TestSceneObject obj;
  const Color c{1, 2, 3};
  obj.setColor(c);
  EXPECT_EQ(obj.getColor(), c);
}

TEST(SceneObjectTest, DefaultColor) {
  const TestSceneObject obj;
  constexpr Color defaultColor{};
  EXPECT_EQ(obj.getColor(), defaultColor);
}

TEST(SceneObjectTest, DefaultConstructor) {
  TestSceneObject obj;
  EXPECT_NO_THROW(obj.getProjectedLines());
  Image image;
  EXPECT_NO_THROW(obj.render(image));
}

TEST(SceneObjectTest, Destructor) {
  auto obj = std::make_unique<const TestSceneObject>();
  EXPECT_NO_THROW(obj.reset());
}

TEST(SceneObjectTest, Inheritance) {
  const std::unique_ptr<SceneObject> obj = std::make_unique<TestSceneObject>();
  EXPECT_NO_THROW(obj->getProjectedLines());
  Image image;
  EXPECT_NO_THROW(obj->render(image));
}