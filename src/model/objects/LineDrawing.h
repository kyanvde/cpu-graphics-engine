#ifndef LINEDRAWING_H
#define LINEDRAWING_H

#include <vector>

#include "model/Image.h"
#include "model/Line.h"
#include "model/SceneObject.h"

class LineDrawing final : public SceneObject {
  std::vector<Line> lines;

 public:
  std::vector<Line> getProjectedLines() override;
  void render(Image& image) override;

  void setLines(std::vector<Line>&& lines) { this->lines = std::move(lines); }
};

#endif  // LINEDRAWING_H
