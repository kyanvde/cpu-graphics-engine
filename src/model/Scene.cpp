#include "Scene.h"

Image Scene::render() { return Image(); }

void Scene::setMaxImageSize(const unsigned int maxImageSize) {
  this->maxImageSize = maxImageSize;
}

void Scene::setBackgroundColor(const Color& backgroundColor) {
  this->backgroundColor = backgroundColor;
}

void Scene::setCamera(const Vec3& camera) { this->camera = camera; }

void Scene::addObject(const SceneObject& object) {
  this->objects.push_back(object);
}
