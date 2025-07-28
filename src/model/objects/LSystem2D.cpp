#include "LSystem2D.h"

#include <stdexcept>

std::vector<Line> LSystem2D::getProjectedLines() {}

void LSystem2D::render(Image& image) {}

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
  this->iterations = iterations;
}
