#include "JsonSceneParser.h"

#include <fstream>

#include "objects/LSystem2DParser.h"
#include "objects/LineDrawingParser.h"

using json = nlohmann::json;

// Constants to reduce magic values
constexpr char TYPE_KEY[] = "type";
constexpr char LINE_DRAWING_TYPE[] = "LineDrawing";
constexpr char LSYSTEM2D_TYPE[] = "LSystem2D";

std::unique_ptr<SceneObject> JsonSceneParser::parseObject(
    const nlohmann::json& objectJson) {
  if (objectJson[TYPE_KEY] == LINE_DRAWING_TYPE) {
    const LineDrawingParser lineDrawingParser;
    return lineDrawingParser.parse(objectJson);
  }

  if (objectJson[TYPE_KEY] == LSYSTEM2D_TYPE) {
    const LSystem2DParser lSystem2DParser;
    return lSystem2DParser.parse(objectJson);
  }

  throw std::runtime_error("Unknown object type: " +
                           objectJson[TYPE_KEY].get<std::string>());
}

Scene JsonSceneParser::parse(const std::string& sceneFile) {
  Scene scene;

  // Load JSON file
  std::ifstream inputFile(sceneFile);
  if (!inputFile.is_open()) {
    throw std::runtime_error("Cannot open scene file");
  }

  json json;
  inputFile >> json;

  // Parse general scene information
  scene.setMaxImageSize(getUnsigned(json, "maxImageSize"));
  scene.setBackgroundColor(Color(getVec3(json, "backgroundColor")));

  if (!json.contains("camera")) {
    throw std::runtime_error("sceneFile needs to specify a camera object");
  }
  scene.setCamera(Vec3(getVec3(json["camera"], "position")));

  // Parse objects
  if (!json.contains("objects") || !json["objects"].is_array()) {
    throw std::runtime_error("sceneFile needs to specify an array of objects");
  }

  for (const auto& objectJson : json["objects"]) {
    scene.addObject(parseObject(objectJson));
  }

  return scene;
}

unsigned int JsonSceneParser::getUnsigned(const json& json,
                                          const std::string& key) {
  if (!json.contains(key)) {
    throw std::runtime_error("Missing key: " + key);
  }
  if (!json[key].is_number_unsigned()) {
    throw std::runtime_error("Field '" + key +
                             "' must be an unsigned integer.");
  }
  return json[key].get<unsigned int>();
}

Vec3 JsonSceneParser::getVec3(const nlohmann::json& json,
                              const std::string& key) {
  if (!json.contains(key)) {
    throw std::runtime_error("Missing key: " + key);
  }

  const auto& arr = json.at(key);
  if (!arr.is_array() || arr.size() != 3) {
    throw std::runtime_error("Expected array of 3 floats for key: " + key);
  }

  for (const auto& val : arr) {
    if (!val.is_number()) {
      throw std::runtime_error("All elements of '" + key + "' must be numbers");
    }
  }

  return {arr[0].get<float>(), arr[1].get<float>(), arr[2].get<float>()};
}

Vec3 JsonSceneParser::getVec3(const nlohmann::json& array) {
  if (!array.is_array() || array.size() != 3) {
    throw std::runtime_error("Expected array of 3 floats");
  }

  for (const auto& val : array) {
    if (!val.is_number()) {
      throw std::runtime_error("All elements of Vec3 must be numbers");
    }
  }

  return {array[0].get<float>(), array[1].get<float>(), array[2].get<float>()};
}

float JsonSceneParser::getFloat(const json& json, const std::string& key) {
  if (!json.contains(key)) {
    throw std::runtime_error("Missing key: " + key);
  }
  if (!json[key].is_number()) {
    throw std::runtime_error("Field '" + key + "' must be a number.");
  }
  return json[key].get<float>();
}

std::string JsonSceneParser::getRequiredString(const json& json,
                                               const std::string& key) {
  if (!json.contains(key)) {
    throw std::runtime_error("Missing key: " + key);
  }
  if (!json[key].is_string()) {
    throw std::runtime_error("Field '" + key + "' must be a string.");
  }
  return json[key].get<std::string>();
}
