#ifndef JSONSCENEPARSER_H
#define JSONSCENEPARSER_H

#include "ISceneParser.h"

class JsonSceneParser final : public ISceneParser {
public:
    Scene parse(const std::string& sceneFile) override;
};

#endif //JSONSCENEPARSER_H
