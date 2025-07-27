#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "math/Transform.h"
#include "model/Color.h"

class SceneObject {
  Color color = {};
  Transform transform;

 protected:
  SceneObject() = default;

 public:
  virtual ~SceneObject() = default;

  virtual void render() = 0;
};

#endif  // SCENEOBJECT_H
