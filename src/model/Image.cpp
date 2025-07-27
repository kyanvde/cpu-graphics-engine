#include "Image.h"

#include <cassert>

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

bool Image::writeTo(const std::string& filename,
                    const ImageWriter& writer) const {
  return writer.write(*this, filename);
}

void Image::clear(const Color color) {
  for (auto& pixel : bitmap) {
    pixel = color;
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
