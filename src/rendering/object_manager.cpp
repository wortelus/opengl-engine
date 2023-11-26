// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation: 22/10/2023

#include <algorithm>
#include "object_manager.h"

char ObjectManager::next_interact_id = 1;

DrawableObject& ObjectManager::addObject(std::unique_ptr<DrawableObject> obj) {
    queued_objects.push_back(std::move(obj));
    return *queued_objects.back();
}

DrawableObject& ObjectManager::assignSkybox(std::unique_ptr<DrawableObject> obj) {
    skybox = std::move(obj);
    return *skybox;
}

//
// Preprocessing
//

void ObjectManager::sortObjects() {
    std::sort(objects.begin(), objects.end(),
              [](const std::unique_ptr<DrawableObject>& a, const std::unique_ptr<DrawableObject>& b) {
                  return a->getShaderAlias() < b->getShaderAlias();
              });
}

void ObjectManager::enqueue(ShaderLoader* shader_loader) {
    for (auto& q_obj: queued_objects) {
        // assign shader alias to the object
        if (int alias = shader_loader->getShaderAlias(q_obj->getShaderName()); alias == SHADER_UNLOADED)
            throw std::runtime_error(
                    "Shader " + q_obj->getShaderName() + " not loaded yet! Assigning shader alias failed.");
        else
            q_obj->assignShaderAlias(alias);

        // load shader if not loaded yet
        Shader* sh = shader_loader->loadShader(q_obj->getShaderAlias());
        q_obj->attach(sh);

        // make use of the loaded shader, and pre-pass uniforms just enough before the rendering loop
        q_obj->notifyModel();
        q_obj->notifyMaterial();

        // assign interaction id to the object if it's marked as one
        if (q_obj->isInteract()) {
            q_obj->setInteractionID(next_interact_id);
            interaction_ids[next_interact_id] = q_obj.get();
            next_interact_id++;
        }

        // add object to the active scene
        objects.push_back(std::move(q_obj));
    }

    // clear the queue
    queued_objects.clear();
}

void ObjectManager::deleteObjects() {
    for (auto& inter_id_obj: inter_ids_to_delete) {
        for (auto it = objects.begin(); it != objects.end(); ++it) {
            if ((*it)->isInteract() && (*it)->getInteractionID() == inter_id_obj) {
                objects.erase(it);
                break;
            }
        }
    }
    inter_ids_to_delete.clear();
}

void ObjectManager::preprocess(ShaderLoader* shader_loader) {
    if (!inter_ids_to_delete.empty())
        deleteObjects();

    if (!queued_objects.empty())
        enqueue(shader_loader);
    else
        sortObjects();
}

//
// Global object transformations
//

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
    queued_objects.clear();
    inter_ids_to_delete.clear();
}

//
// Interactions with concrete objects
//

DrawableObject* ObjectManager::getByInteractID(const char& id) {
    return interaction_ids[id];
}

void ObjectManager::deleteByInteractID(const char& id) {
    inter_ids_to_delete.push_back(id);
}