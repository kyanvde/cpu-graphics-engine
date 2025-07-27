#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "math/Transform.h"
#include "model/Color.h"
#include "model/Line.h"

class Image;

class SceneObject {
  Color color = {0, 0, 255};
  Transform transform;

 protected:
  SceneObject() = default;

 public:
  virtual ~SceneObject() = default;

  virtual std::vector<Line> getProjectedLines() = 0;
  virtual void render(Image& image) = 0;

  void setColor(const Color& color) { this->color = color; }
  [[nodiscard]] Color getColor() const { return color; }
};

#endif  // SCENEOBJECT_H
