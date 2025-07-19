#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "ISceneObject.h"

class Scene {
    std::vector<ISceneObject> objects;
};

#endif //SCENE_H
