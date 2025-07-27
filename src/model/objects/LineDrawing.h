#ifndef LINEDRAWING_H
#define LINEDRAWING_H

#include <vector>

#include "model/Line.h"
#include "model/SceneObject.h"

class LineDrawing final : public SceneObject {
  std::vector<Line> lines;

 public:
  void render() override;

  void setLines(const std::vector<Line>& lines) { this->lines = lines; }
};

#endif  // LINEDRAWING_H
