#include "Projector.h"

#include <iostream>
Vec3 Projector::projectPoint(const Vec3& point, double focalLength) {
  double xCoord = focalLength * point.x / -point.z;
  double yCoord = focalLength * point.y / -point.z;

  return {xCoord, yCoord, point.z};
}
