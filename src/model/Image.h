#ifndef IMAGE_H
#define IMAGE_H

#include <iosfwd>
#include <string>
#include <vector>

#include "Color.h"
#include "Line.h"

class ImageWriter;

const Color ERROR_COLOR = Color(255, 0, 0);

class Image {
  unsigned int width, height;
  std::vector<Color> bitmap;

  double scaleFactor, moveX, moveY;

 public:
  explicit Image(Color color = ERROR_COLOR);

  Image(unsigned int width, unsigned int height, Color color = Color());
  Image(const std::vector<Line>& lines, const Color& backgroundColor,
        unsigned int maxImageSize);

  bool writeTo(const std::string& filename, const ImageWriter& writer) const;

  void clear(Color color = Color());
  void drawLine(const Line& line, const Color& color);

  Color& operator()(unsigned int xCoord, unsigned int yCoord);
  Color const& operator()(unsigned int xCoord, unsigned int yCoord) const;

  unsigned int getWidth() const;
  unsigned int getHeight() const;
  [[nodiscard]] double getScaleFactor() const { return scaleFactor; }
  [[nodiscard]] double getMoveX() const { return moveX; }
  [[nodiscard]] double getMoveY() const { return moveY; }
};

#endif  // IMAGE_H
