#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>

#include "Color.h"

class ImageWriter;

class Image {
    unsigned int width, height;
    std::vector<Color> bitmap;

public:
    Image(unsigned int width, unsigned int height, Color color = Color());

    bool writeTo(const std::string& filename, const ImageWriter& writer) const;

    void clear(Color color = Color());

    Color& operator()(unsigned int x, unsigned int y);
    Color const& operator()(unsigned int x, unsigned int y) const;

    unsigned int getWidth() const;
    unsigned int getHeight() const;
};

#endif //IMAGE_H
