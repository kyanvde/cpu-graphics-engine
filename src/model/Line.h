#ifndef LINE_H
#define LINE_H
#include "math/Vec3.h"

struct Line {
  Vec3 from;
  Vec3 to;

  Line(const Vec3 &from, const Vec3 &to) : from(from), to(to) {}
};
#endif  // LINE_H
