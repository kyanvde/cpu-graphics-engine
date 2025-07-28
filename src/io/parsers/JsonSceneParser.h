#ifndef JSONSCENEPARSER_H
#define JSONSCENEPARSER_H

#include <nlohmann/json.hpp>

#include "io/parsers/SceneParser.h"

class JsonSceneParser final : public SceneParser {
 public:
  Scene parse(const std::string& sceneFile) override;

  static unsigned int getUnsigned(const nlohmann::json& json,
                                  const std::string& key);
  static Vec3 getVec3(const nlohmann::json& json, const std::string& key);
  static Vec3 getVec3(const nlohmann::json& array);
  static float getFloat(const nlohmann::json& json, const std::string& key);
  static std::string getRequiredString(const nlohmann::json& json,
                                       const std::string& key);
};

#endif  // JSONSCENEPARSER_H
