#ifndef LSYSTEM2DPARSER_H
#define LSYSTEM2DPARSER_H

#include "io/parsers/SceneObjectParser.h"

class LSystem2DParser final : public SceneObjectParser {
 public:
  std::unique_ptr<SceneObject> parse(const nlohmann::json& json) const override;
};

#endif  // LSYSTEM2DPARSER_H
