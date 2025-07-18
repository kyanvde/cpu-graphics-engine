#ifndef ISCENEPARSER_H
#define ISCENEPARSER_H

#include <string>
#include "../model/Scene.h"

class ISceneParser {
public:
    virtual ~ISceneParser() = default;
    virtual Scene parse(const std::string& sceneFile) = 0;
};

#endif //ISCENEPARSER_H
