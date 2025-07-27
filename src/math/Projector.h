#ifndef PROJECTOR_H
#define PROJECTOR_H

#include "Vec3.h"

class Projector {
 public:
  static Vec3 projectPoint(const Vec3& point, double d);
};

#endif  // PROJECTOR_H
