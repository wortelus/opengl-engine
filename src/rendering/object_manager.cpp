// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation: 22/10/2023

#include <algorithm>
#include "object_manager.h"

DrawableObject& ObjectManager::addObject(std::unique_ptr<DrawableObject> obj) {
    queued_objects.push_back(std::move(obj));
    return *queued_objects.back();
}

DrawableObject& ObjectManager::assignSkybox(std::unique_ptr<DrawableObject> obj) {
    skybox = std::move(obj);
    return *skybox;
}

void ObjectManager::enqueue(ShaderLoader* shader_loader) {
    for (auto& q_obj: queued_objects) {
        if (int alias = shader_loader->getShaderAlias(q_obj->getShaderName()); alias == SHADER_UNLOADED)
            throw std::runtime_error("Shader " + q_obj->getShaderName() + " not loaded yet! Assigning shader alias failed.");
        else
            q_obj->assignShaderAlias(alias);

        Shader* sh = shader_loader->loadShader(q_obj->getShaderAlias());
        q_obj->attach(sh);

        // make use of the loaded shader, and pre-pass uniforms just enough before the rendering loop
        q_obj->notifyModel();
        q_obj->notifyMaterial();

        objects.push_back(std::move(q_obj));
    }
    queued_objects.clear();
}

void ObjectManager::preprocess(ShaderLoader* shader_loader) {
    if (queued_objects.empty())
        return;

    enqueue(shader_loader);
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
