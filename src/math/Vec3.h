#ifndef VEC3_H
#define VEC3_H

#include <cmath>

struct Vec3 {
  double x, y, z;

  Vec3() = default;

  Vec3(const double xCoord, const double yCoord, const double zCoord)
      : x(xCoord), y(yCoord), z(zCoord) {}

  bool operator==(const Vec3& other) const {
    return x == other.x && y == other.y && z == other.z;
  }

  Vec3 operator+(const Vec3& other) const {
    return {x + other.x, y + other.y, z + other.z};
  }

  Vec3 operator-(const Vec3& other) const {
    return {x - other.x, y - other.y, z - other.z};
  }

  Vec3 operator*(const double scalar) const {
    return {x * scalar, y * scalar, z * scalar};
  }

  Vec3 operator*(const Vec3& other) const {
    return {x * other.x, y * other.y, z * other.z};
  }

  Vec3 cross(const Vec3& other) const {
    return {(y * other.z) - (z * other.y), (z * other.x) - (x * other.z),
            (x * other.y) - (y * other.x)};
  }

  Vec3 normalize() const {
    const double len = std::sqrt((x * x) + (y * y) + (z * z));
    if (len == 0.0F) {
      return {0, 0, 0};
    }
    return {x / len, y / len, z / len};
  }
};

#endif  // VEC3_H
