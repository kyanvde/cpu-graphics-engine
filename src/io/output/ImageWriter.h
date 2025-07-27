#ifndef IMAGEWRITER_H
#define IMAGEWRITER_H

#include <string>

#include "../../model/Image.h"

class ImageWriter {
public:
    virtual ~ImageWriter() = default;
    virtual bool write(const Image& image, const std::string& filename) const = 0;
};

#endif //IMAGEWRITER_H
