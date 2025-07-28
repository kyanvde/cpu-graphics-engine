#include "LSystem2DParser.h"

#include "io/parsers/JsonSceneParser.h"
#include "model/objects/LSystem2D.h"

std::unique_ptr<SceneObject> LSystem2DParser::parse(
    const nlohmann::json& json) const {
  LSystem2D lSystem;

  // Fetch all letters of the alphabet
  if (!json.contains("alphabet") || !json["alphabet"].is_array()) {
    throw std::runtime_error(
        "object of type LSystem2D needs to contain an array of alphabet "
        "characters");
  }

  for (const auto& character : json["alphabet"]) {
    if (!character.is_string() || character.get<std::string>().length() != 1) {
      throw std::runtime_error("alphabet entries must be single characters");
    }
    lSystem.addSymbol(character.get<std::string>()[0]);
  }

  // Parse draw commands
  if (json.contains("draw") && json["draw"].is_array()) {
    for (const auto& character : json["draw"]) {
      if (!character.is_string() ||
          character.get<std::string>().length() != 1) {
        throw std::runtime_error("draw entries must be single characters");
      }
      lSystem.setDrawSymbol(character.get<std::string>()[0], true);
    }
  }

  // Parse replacement rules
  if (json.contains("rules") && json["rules"].is_array()) {
    for (const auto& rule : json["rules"]) {
      if (!rule.is_array() || rule.size() != 2) {
        throw std::runtime_error(
            "each rule must be a 2-element array [from, to]");
      }
      std::string from = rule[0].get<std::string>();
      std::string replacement = rule[1].get<std::string>();
      if (from.length() != 1) {
        throw std::runtime_error("rule 'from' must be a single character");
      }
      lSystem.addReplacementRule(from[0], replacement);
    }
  }

  lSystem.setInitiator(JsonSceneParser::getRequiredString(json, "initiator"));
  lSystem.setAngle(JsonSceneParser::getFloat(json, "angle"));
  lSystem.setStartingAngle(JsonSceneParser::getFloat(json, "startingAngle"));
  lSystem.setIterations(JsonSceneParser::getUnsigned(json, "iterations"));

  return std::make_unique<LSystem2D>(std::move(lSystem));
}
