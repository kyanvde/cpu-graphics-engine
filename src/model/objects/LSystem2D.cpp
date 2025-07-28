#include "LSystem2D.h"

#include <stack>
#include <stdexcept>

#include "math/MathUtils.h"
#include "math/Projector.h"
#include "model/Image.h"

std::vector<Line> LSystem2D::getProjectedLines() {
  Vec3 pencil{0, 0, 0};

  std::string sys_string = initiator;
  for (unsigned int iterations = 0; iterations < nrIterations; iterations++) {
    std::string new_string;
    for (const char& symbol : sys_string) {
      if (alphabet.find(symbol) != alphabet.end()) {
        new_string += replacement.find(symbol)->second;
      } else {
        new_string += symbol;
      }
    }
    sys_string = new_string;
  }

  double currentAngle = startingAngle;
  std::stack<double> angleStack;
  std::stack<Vec3> pencilStack;

  std::vector<Line> lines;
  for (const char& symbol : sys_string) {
    if (alphabet.find(symbol) != alphabet.end()) {
      Vec3 newPencil = pencil + Vec3{cos(MathUtils::degToRad(currentAngle)),
                                     sin(MathUtils::degToRad(currentAngle)), 0};
      if (alphabet.find(symbol)->second) {
        lines.emplace_back(pencil, newPencil);
      }
      pencil = newPencil;
    } else if (symbol == '+') {
      currentAngle += angle;
    } else if (symbol == '-') {
      currentAngle -= angle;
    } else if (symbol == '[') {
      angleStack.push(currentAngle);
      pencilStack.push(pencil);
    } else if (symbol == ']') {
      currentAngle = angleStack.top();
      angleStack.pop();

      pencil = pencilStack.top();
      pencilStack.pop();
    }
  }

  return lines;
}

void LSystem2D::render(Image& image) {
  std::vector<Line> projectedLines = getProjectedLines();
  for (Line& line : projectedLines) {
    line.from = line.from * image.getScaleFactor();
    line.to = line.to * image.getScaleFactor();

    line.from = line.from + Vec3(image.getMoveX(), image.getMoveY(), 0);
    line.to = line.to + Vec3(image.getMoveX(), image.getMoveY(), 0);

    image.drawLine(line, getColor());
  }
}

void LSystem2D::addSymbol(const char symbol) {
  this->alphabet.insert({symbol, false});
}

void LSystem2D::setDrawSymbol(const char symbol, const bool value) {
  const auto iterator = this->alphabet.find(symbol);
  if (iterator == this->alphabet.end()) {
    throw std::runtime_error("Attempted to set draw value for unknown symbol");
  }
  iterator->second = value;
}

void LSystem2D::addReplacementRule(char from, const std::string& replacement) {
  this->replacement.insert({from, replacement});
}

void LSystem2D::setInitiator(const std::string& initiator) {
  this->initiator = initiator;
}

void LSystem2D::setAngle(const double angle) { this->angle = angle; }

void LSystem2D::setStartingAngle(const double angle) {
  this->startingAngle = angle;
}
void LSystem2D::setIterations(const unsigned int iterations) {
  this->nrIterations = iterations;
}
