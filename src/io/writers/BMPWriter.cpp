#include "BMPWriter.h"

#include <fstream>

namespace {
#pragma pack(push, 1)
struct BMPFileHeader {
  [[maybe_unused]] uint16_t fileType{0x4D42};  // 'BM'
  uint32_t fileSize{0};
  [[maybe_unused]] uint16_t reserved1{0};
  [[maybe_unused]] uint16_t reserved2{0};
  [[maybe_unused]] uint32_t offsetData{54};  // Header size (14 + 40)
};

struct BMPInfoHeader {
  [[maybe_unused]] uint32_t size{40};
  int32_t width{0};
  int32_t height{0};  // Bottom-up
  [[maybe_unused]] uint16_t planes{1};
  [[maybe_unused]] uint16_t bitCount{24};  // 24-bit RGB
  [[maybe_unused]] uint32_t compression{0};
  uint32_t imageSize{0};
  [[maybe_unused]] int32_t xPixelsPerMeter{2835};  // 72 DPI
  [[maybe_unused]] int32_t yPixelsPerMeter{2835};
  [[maybe_unused]] uint32_t colorsUsed{0};
  [[maybe_unused]] uint32_t importantColors{0};
};
#pragma pack(pop)
}  // namespace

bool BMPWriter::write(const Image& image, const std::string& filename) const {
  const int width = static_cast<int>(image.getWidth());
  const int height = static_cast<int>(image.getHeight());
  const int rowStride = ((width * 3 + 3) / 4) * 4;
  const int paddingSize = rowStride - (width * 3);

  BMPFileHeader fileHeader;
  BMPInfoHeader infoHeader;

  infoHeader.width = width;
  infoHeader.height = height;
  infoHeader.imageSize = rowStride * height;
  fileHeader.fileSize =
      sizeof(fileHeader) + sizeof(infoHeader) + infoHeader.imageSize;

  std::ofstream out(filename, std::ios::binary);
  if (!out) {
    return false;
  }

  out.write(reinterpret_cast<const char*>(&fileHeader), sizeof(fileHeader));
  out.write(reinterpret_cast<const char*>(&infoHeader), sizeof(infoHeader));

  for (int yCoord = height - 1; yCoord >= 0; --yCoord) {
    uint8_t padding[3] = {0, 0, 0};
    for (int xCoord = 0; xCoord < width; ++xCoord) {
      const Color& color = image(xCoord, yCoord);
      uint8_t bgr[3] = {color.b, color.g, color.r};
      out.write(reinterpret_cast<char*>(bgr), 3);
    }
    out.write(reinterpret_cast<char*>(padding), paddingSize);
  }

  return true;
}
