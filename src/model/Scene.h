#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>

#include "Image.h"
#include "SceneObject.h"

class Scene {
  unsigned int maxImageSize = 0;

  Color backgroundColor = {};

  Vec3 camera = {};

  std::vector<std::unique_ptr<SceneObject>> objects;

 public:
  Image render() const;

  void setMaxImageSize(unsigned int maxImageSize);

  void setBackgroundColor(const Color& backgroundColor);

  void setCamera(const Vec3& camera);

  void addObject(std::unique_ptr<SceneObject> object);

  unsigned int getMaxImageSize() const;
  Color getBackgroundColor() const;
  Vec3 getCamera() const;
  const std::vector<std::unique_ptr<SceneObject>>& getObjects();
};

#endif  // SCENE_H
