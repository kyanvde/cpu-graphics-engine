#include "Image.h"

#include <cassert>

#include "../io/output/ImageWriter.h"

Image::Image(const Color color) {
    this->width = 404;
    this->height = 404;
    this->bitmap = std::vector<Color>(this->width * this->height, color);
}

Image::Image(const unsigned int width, const unsigned int height, const Color color) {
    this->width = width;
    this->height = height;
    this->bitmap = std::vector(width * height, color);
}

bool Image::writeTo(const std::string& filename, const ImageWriter& writer) const {
    return writer.write(*this, filename);
}

void Image::clear(const Color color) {
    for (auto & i : bitmap) {
        i = color;
    }
}

Color& Image::operator()(const unsigned int x, const unsigned int y) {
    assert(x < this->width);
    assert(y < this->height);
    return bitmap.at(x * height + y);
}

Color const& Image::operator()(const unsigned int x, const unsigned int y) const {
    assert(x < this->width);
    assert(y < this->height);
    return bitmap.at(x * height + y);
}

unsigned int Image::getWidth() const {
    return this->width;
}

unsigned int Image::getHeight() const {
    return this->height;
}
