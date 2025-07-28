#include "JsonSceneParser.h"

#include <fstream>

#include "objects/LSystem2DParser.h"
#include "objects/LineDrawingParser.h"

using json = nlohmann::json;

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
    if (objectJson["type"] == "LineDrawing") {
      LineDrawingParser lineDrawingParser;
      scene.addObject(lineDrawingParser.parse(objectJson));
    } else if (objectJson["type"] == "LSystem2D") {
      LSystem2DParser lSystem2DParser;
      scene.addObject(lSystem2DParser.parse(objectJson));
    }
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
