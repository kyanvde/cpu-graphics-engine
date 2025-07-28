#ifndef SCENEOBJECTPARSER_H
#define SCENEOBJECTPARSER_H

#include <memory>
#include <nlohmann/json.hpp>

#include "model/SceneObject.h"

class SceneObjectParser {
 protected:
  SceneObjectParser() = default;

 public:
  virtual std::unique_ptr<SceneObject> parse(
      const nlohmann::json& json) const = 0;
  virtual ~SceneObjectParser() = default;
};

#endif  // SCENEOBJECTPARSER_H
