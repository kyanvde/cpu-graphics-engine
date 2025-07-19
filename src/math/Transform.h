#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "vec3.h"

struct Transform {
    Vec3 position = {0, 0, 0};
    Vec3 rotation = {0, 0, 0};
    Vec3 scale = {0, 0, 0};
}

#endif // TRANSFORM_H
