#include "Projector.h"

#include <iostream>
Vec3 Projector::projectPoint(const Vec3& point, double d) {
  float xCoord = d * point.x / -point.z;
  float yCoord = d * point.y / -point.z;

  return {xCoord, yCoord, point.z};
}
