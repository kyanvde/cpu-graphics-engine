#ifndef SCENEPARSER_H
#define SCENEPARSER_H

#include <string>
#include "../../model/Scene.h"

class SceneParser {
public:
    virtual ~SceneParser() = default;
    virtual Scene parse(const std::string& sceneFile) = 0;
};

#endif //SCENEPARSER_H
