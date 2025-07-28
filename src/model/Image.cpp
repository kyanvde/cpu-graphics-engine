#include "Image.h"

#include <algorithm>
#include <cassert>
#include <sstream>

#include "Line.h"
#include "io/writers/ImageWriter.h"

static constexpr unsigned int ERROR_WH = 404;

Image::Image(const Color color) {
  this->width = ERROR_WH;
  this->height = ERROR_WH;
  this->bitmap = std::vector(this->width * this->height, color);
}

Image::Image(const unsigned int width, const unsigned int height,
             const Color color) {
  this->width = width;
  this->height = height;
  this->bitmap = std::vector(width * height, color);
}

Image::Image(const std::vector<Line>& lines, const Color& backgroundColor,
             const unsigned int maxImageSize) {
  double minX = std::numeric_limits<double>::max();
  double maxX = std::numeric_limits<double>::lowest();
  double minY = std::numeric_limits<double>::max();
  double maxY = std::numeric_limits<double>::lowest();

  for (const Line& line : lines) {
    const double firstX = line.from.x;
    const double firstY = line.from.y;
    const double secondX = line.to.x;
    const double secondY = line.to.y;

    minX = std::min(minX, std::min(firstX, secondX));
    maxX = std::max(maxX, std::max(firstX, secondX));
    minY = std::min(minY, std::min(firstY, secondY));
    maxY = std::max(maxY, std::max(firstY, secondY));
  }

  const double xRange = maxX - minX;
  const double yRange = maxY - minY;
  const double dominantRange = std::max(xRange, yRange);

  unsigned int imageWidth = 0;
  unsigned int imageHeight = 0;

  if (dominantRange == 0) {
    // All points are at the same coordinate, fallback to minimum size 1x1
    imageWidth = 1;
    imageHeight = 1;
  } else {
    imageWidth = static_cast<unsigned int>(
        std::ceil(maxImageSize * (xRange / dominantRange)));
    imageHeight = static_cast<unsigned int>(
        std::ceil(maxImageSize * (yRange / dominantRange)));

    // Ensure width and height are at least 1
    if (imageWidth == 0) {
      imageWidth = 1;
    }
    if (imageHeight == 0) {
      imageHeight = 1;
    }
  }
  constexpr double scaleMultiplier = 0.95;
  scaleFactor = scaleMultiplier * (imageWidth / xRange);

  const double centerX = scaleFactor * ((minX + maxX) / 2);
  const double centerY = scaleFactor * ((minY + maxY) / 2);

  moveX = static_cast<int>(imageWidth / 2) - centerX;
  moveY = static_cast<int>(imageHeight / 2) - centerY;

  this->width = imageWidth;
  this->height = imageHeight;
  this->bitmap = std::vector(width * height, backgroundColor);
}

bool Image::writeTo(const std::string& filename,
                    const ImageWriter& writer) const {
  return writer.write(*this, filename);
}

void Image::clear(const Color color) {
  for (auto& pixel : bitmap) {
    pixel = color;
  }
}

void Image::drawLine(const Line& line, const Color& color) {
  int x0Coord = static_cast<int>(std::round(line.from.x));
  int y0Coord = static_cast<int>(std::round(line.from.y));
  int x1Coord = static_cast<int>(std::round(line.to.x));
  int y1Coord = static_cast<int>(std::round(line.to.y));

  // Clamp to image bounds
  x0Coord = std::clamp(x0Coord, 0, static_cast<int>(width) - 1);
  y0Coord = std::clamp(y0Coord, 0, static_cast<int>(height) - 1);
  x1Coord = std::clamp(x1Coord, 0, static_cast<int>(width) - 1);
  y1Coord = std::clamp(y1Coord, 0, static_cast<int>(height) - 1);

  const bool steep = abs(y1Coord - y0Coord) > abs(x1Coord - x0Coord);

  // Swap x and y if the line is steep
  if (steep) {
    std::swap(x0Coord, y0Coord);
    std::swap(x1Coord, y1Coord);
  }

  // Make sure we draw from left to right
  if (x0Coord > x1Coord) {
    std::swap(x0Coord, x1Coord);
    std::swap(y0Coord, y1Coord);
  }

  const int deltaX = x1Coord - x0Coord;
  const int deltaY = abs(y1Coord - y0Coord);
  int error = deltaX / 2;
  const int yStep = (y0Coord < y1Coord) ? 1 : -1;

  int y = y0Coord;
  for (int xCoord = x0Coord; xCoord <= x1Coord; ++xCoord) {
    if (steep) {
      (*this)(y, xCoord) = color;  // if steep, swap back
    } else {
      (*this)(xCoord, y) = color;
    }

    error -= deltaY;
    if (error < 0) {
      y += yStep;
      error += deltaX;
    }
  }
}

Color& Image::operator()(const unsigned int xCoord, const unsigned int yCoord) {
  assert(xCoord < this->width);
  assert(yCoord < this->height);
  return bitmap.at((xCoord * height) + yCoord);
}

Color const& Image::operator()(const unsigned int xCoord,
                               const unsigned int yCoord) const {
  assert(xCoord < this->width);
  assert(yCoord < this->height);
  return bitmap.at((xCoord * height) + yCoord);
}

unsigned int Image::getWidth() const { return this->width; }

unsigned int Image::getHeight() const { return this->height; }
