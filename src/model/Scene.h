#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "Image.h"
#include "SceneObject.h"

class Scene {
  unsigned int maxImageSize = 0;

  Color backgroundColor = {};

  Vec3 camera;

  std::vector<SceneObject> objects;

 public:
  Image render();

  void setMaxImageSize(unsigned int maxImageSize);

  void setBackgroundColor(const Color& backgroundColor);

  void setCamera(const Vec3& camera);

  void addObject(const SceneObject& object);
};

#endif  // SCENE_H
