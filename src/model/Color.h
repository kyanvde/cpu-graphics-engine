#ifndef COLOR_H
#define COLOR_H

#include <cstdint>

#include "math/Vec3.h"

struct Color {
  uint8_t r, g, b;

  Color() = default;

  Color(const uint8_t red, const uint8_t green, const uint8_t blue) {
    this->r = red;
    this->g = green;
    this->b = blue;
  }

  explicit Color(const Vec3& vec3) {
    this->r = static_cast<uint8_t>(vec3.x);
    this->g = static_cast<uint8_t>(vec3.y);
    this->b = static_cast<uint8_t>(vec3.z);
  }

  bool operator==(const Color& other) const {
    return r == other.r && g == other.g && b == other.b;
  }
};

#endif  // COLOR_H
