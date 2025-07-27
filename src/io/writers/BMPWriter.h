#ifndef BMPWRITER_H
#define BMPWRITER_H
#include "ImageWriter.h"

class BMPWriter final : public ImageWriter {
 public:
  bool write(const Image& image, const std::string& filename) const override;
};

#endif  // BMPWRITER_H
