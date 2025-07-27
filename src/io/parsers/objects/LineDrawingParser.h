#ifndef LINEDRAWINGPARSER_H
#define LINEDRAWINGPARSER_H

#include "io/parsers/SceneObjectParser.h"

class LineDrawingParser final : public SceneObjectParser {
 public:
  std::unique_ptr<SceneObject> parse(const nlohmann::json& json) const override;
};

#endif  // LINEDRAWINGPARSER_H
