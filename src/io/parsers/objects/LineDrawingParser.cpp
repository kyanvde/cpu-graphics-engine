#include "LineDrawingParser.h"

#include <iostream>

#include "io/parsers/JsonSceneParser.h"
#include "model/objects/LineDrawing.h"

std::unique_ptr<SceneObject> LineDrawingParser::parse(
    const nlohmann::json& json) const {
  LineDrawing lineDrawing;

  std::vector<Vec3> points;
  // Fetch all points
  if (!json.contains("points") || !json["points"].is_array()) {
    throw std::runtime_error(
        "object of type LineDrawing needs to contain an array of points");
  }

  for (const auto& pointJson : json["points"]) {
    points.push_back(JsonSceneParser::getVec3(pointJson));
  }

  std::vector<Line> lines;
  // Create all lines
  if (!json.contains("lines") || !json["lines"].is_array()) {
    throw std::runtime_error(
        "object of type LineDrawings needs to contain an array of lines");
  }

  for (const auto& lineJson : json["lines"]) {
    if (!lineJson.is_array() || lineJson.size() != 2 ||
        !lineJson[0].is_number_unsigned() ||
        !lineJson[1].is_number_unsigned()) {
      throw std::runtime_error(
          "Each line must be an array of 2 unsigned integers.");
    }

    lines.emplace_back(points[lineJson[0].get<unsigned int>()],
                       points[lineJson[1].get<unsigned int>()]);
  }

  lineDrawing.setLines(std::move(lines));
  lineDrawing.setColor(Color(JsonSceneParser::getVec3(json["color"])));

  return std::make_unique<LineDrawing>(std::move(lineDrawing));
}
