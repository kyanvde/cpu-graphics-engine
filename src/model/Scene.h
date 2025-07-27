#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "Image.h"
#include "SceneObject.h"

class Scene {
    std::vector<SceneObject> objects;

public:
    Image render();
};

#endif //SCENE_H
