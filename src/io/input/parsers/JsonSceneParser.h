#ifndef JSONSCENEPARSER_H
#define JSONSCENEPARSER_H

#include "../SceneParser.h"

class JsonSceneParser final : public SceneParser {
public:
    Scene parse(const std::string& sceneFile) override;
};

#endif //JSONSCENEPARSER_H
