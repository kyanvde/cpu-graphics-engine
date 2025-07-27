#ifndef LINEDRAWING_H
#define LINEDRAWING_H

#include <vector>

#include "model/SceneObject.h"

class LineDrawing final : public SceneObject {
  std::vector<Vec3> points;
  std::vector<std::pair<int, int>> lines;

 public:
  void render() override;
};

#endif  // LINEDRAWING_H
