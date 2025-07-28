#ifndef LSYSTEM2D_H
#define LSYSTEM2D_H

#include <map>
#include <set>
#include <string>
#include <vector>

#include "model/SceneObject.h"

class LSystem2D final : public SceneObject {
  std::set<char> alphabet;
  std::map<char, bool> draw;
  std::map<char, std::string> replacement;
  std::string initiator;
  double angle = 90;
  double startingAngle = 0;
  unsigned int iterations = 1;

 public:
  std::vector<Line> getProjectedLines() override;
  void render(Image& image) override;
};

#endif  // LSYSTEM2D_H
