#include "LineDrawing.h"

#include <iostream>

#include "math/Projector.h"

std::vector<Line> LineDrawing::getProjectedLines() {
  std::vector<Line> projectedLines;
  for (Line& line : lines) {
    projectedLines.emplace_back(Projector::projectPoint(line.from, 1),
                                Projector::projectPoint(line.to, 1));
  }
  return projectedLines;
}

void LineDrawing::render(Image& image) {
  std::vector<Line> projectedLines = getProjectedLines();

  for (Line& line : projectedLines) {
    line.from = line.from * image.getScaleFactor();
    line.to = line.to * image.getScaleFactor();

    line.from = line.from + Vec3(image.getMoveX(), image.getMoveY(), 0);
    line.to = line.to + Vec3(image.getMoveX(), image.getMoveY(), 0);

    image.drawLine(line, getColor());
  }
}
