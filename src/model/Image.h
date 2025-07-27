#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>

#include "Color.h"

class ImageWriter;

const Color ERROR_COLOR = Color(255, 0, 0);

class Image {
  unsigned int width, height;
  std::vector<Color> bitmap;

 public:
  explicit Image(Color color = ERROR_COLOR);

  Image(unsigned int width, unsigned int height, Color color = Color());

  bool writeTo(const std::string& filename, const ImageWriter& writer) const;

  void clear(Color color = Color());

  Color& operator()(unsigned int xCoord, unsigned int yCoord);
  Color const& operator()(unsigned int xCoord, unsigned int yCoord) const;

  unsigned int getWidth() const;
  unsigned int getHeight() const;
};

#endif  // IMAGE_H
