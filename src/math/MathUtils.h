#ifndef MATHUTILS_H
#define MATHUTILS_H

#include <cmath>

namespace MathUtils {

#ifndef M_PI
constexpr double PI = 3.14159265358979323846;
#else
constexpr double PI = M_PI;
#endif

inline double degToRad(const double degrees) { return degrees * (PI / 180.0); }

inline double radToDeg(const double radians) { return radians * (180.0 / PI); }

}  // namespace MathUtils

#endif  // MATHUTILS_H
