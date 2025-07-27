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

  scaleFactor = 0.95 * (imageWidth / xRange);

  const double centerX = scaleFactor * ((minX + maxX) / 2);
  const double centerY = scaleFactor * ((minY + maxY) / 2);

  moveX = (imageWidth / 2) - centerX;
  moveY = (imageHeight / 2) - centerY;

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
  int x0 = static_cast<int>(std::round(line.from.x));
  int y0 = static_cast<int>(std::round(line.from.y));
  int x1 = static_cast<int>(std::round(line.to.x));
  int y1 = static_cast<int>(std::round(line.to.y));

  // Clamp to image bounds
  x0 = std::clamp(x0, 0, static_cast<int>(width) - 1);
  y0 = std::clamp(y0, 0, static_cast<int>(height) - 1);
  x1 = std::clamp(x1, 0, static_cast<int>(width) - 1);
  y1 = std::clamp(y1, 0, static_cast<int>(height) - 1);

  if (x0 >= this->width || y0 >= this->height || x1 >= this->width ||
      y1 > this->height) {
    std::stringstream ss;
    ss << "Drawing line from (" << x0 << "," << y0 << ") to (" << x1 << ","
       << y1 << ") in image of width " << this->width << " and height "
       << this->height;
    throw std::runtime_error(ss.str());
  }
  if ((x0 > x1) || ((x0 == x1) && (y0 > y1))) {
    // Ensure p0->p1 goes from left to right (or from bottom to top if perfectly
    // vertical)
    std::swap(x0, x1);
    std::swap(y0, y1);
  }

  if (x0 == x1) {
    // Special case for vertical line
    for (int px = 0; px <= (y1 - y0); px++) {
      (*this)(x0, y0 + px) = color;
    }
  } else if (y0 == y1) {
    // Special case for horizontal line
    for (int px = 0; px <= (x1 - x0); px++) {
      (*this)(x0 + px, y0) = color;
    }
  } else {
    // Diagonal line, 3 cases depending on slope
    double m = ((double)y1 - (double)y0) / ((double)x1 - (double)x0);
    if (-1.0 <= m && m <= 1.0) {
      for (int px = 0; px <= x1 - x0; px++) {
        (*this)(x0 + px, (unsigned int)round(y0 + m * px)) = color;
      }
    } else if (m > 1.0) {
      for (int px = 0; px <= y1 - y0; px++) {
        (*this)((unsigned int)round(x0 + (px / m)), y0 + px) = color;
      }
    } else if (m < -1.0) {
      for (int px = 0; px <= y0 - y1; px++) {
        (*this)((unsigned int)round(x0 - (px / m)), y0 - px) = color;
      }
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
