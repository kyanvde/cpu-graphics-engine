#ifndef LSYSTEM2D_H
#define LSYSTEM2D_H

#include <map>
#include <string>
#include <vector>

#include "model/SceneObject.h"

class LSystem2D final : public SceneObject {
  std::map<const char, bool> alphabet;
  std::map<const char, std::string> replacement;
  std::string initiator;
  double angle = 0;
  double startingAngle = 0;
  unsigned int iterations = 1;

 public:
  std::vector<Line> getProjectedLines() override;
  void render(Image& image) override;

  void addSymbol(char symbol);
  void setDrawSymbol(char symbol, bool value);
  void addReplacementRule(char from, const std::string& replacement);
  void setInitiator(const std::string& initiator);
  void setAngle(double angle);
  void setStartingAngle(double angle);
  void setIterations(unsigned int iterations);
};

#endif  // LSYSTEM2D_H
