#include "Scene.h"

#include <iostream>

Image Scene::render() const {
  std::vector<Line> lines;
  for (const std::unique_ptr<SceneObject>& object : objects) {
    const std::vector<Line>& objLines = object->getProjectedLines();
    lines.insert(lines.end(), objLines.begin(), objLines.end());
  }

  Image image(lines, backgroundColor, maxImageSize);
  for (const std::unique_ptr<SceneObject>& object : objects) {
    object->render(image);
  }

  return image;
}

void Scene::setMaxImageSize(const unsigned int maxImageSize) {
  this->maxImageSize = maxImageSize;
}

void Scene::setBackgroundColor(const Color& backgroundColor) {
  this->backgroundColor = backgroundColor;
}

void Scene::setCamera(const Vec3& camera) { this->camera = camera; }

void Scene::addObject(std::unique_ptr<SceneObject> object) {
  this->objects.push_back(std::move(object));
}
