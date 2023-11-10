// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation: 22/10/2023

#include <algorithm>
#include "object_manager.h"

DrawableObject& ObjectManager::addObject(std::unique_ptr<DrawableObject> obj) {
    objects.push_back(std::move(obj));
    return *objects.back();
}

DrawableObject& ObjectManager::assignSkybox(std::unique_ptr<DrawableObject> obj) {
    skybox = std::move(obj);
    return *skybox;
}

void ObjectManager::preprocess() {
    std::sort(objects.begin(), objects.end(),
              [](const std::unique_ptr<DrawableObject>& a, const std::unique_ptr<DrawableObject>& b) {
                  return a->getShaderAlias() < b->getShaderAlias();
              });
}

void ObjectManager::translate(const glm::vec3& translation) {
    for (auto& obj: objects) {
        obj->translate(translation);
    }
}

void ObjectManager::rotate(const glm::vec3& axis_degrees) {
    for (auto& obj: objects) {
        obj->rotate(axis_degrees);
    }
}

void ObjectManager::scale(const glm::vec3& scale) {
    for (auto& obj: objects) {
        obj->scale(scale);
    }
}

ObjectManager::~ObjectManager() {
    objects.clear();
}
