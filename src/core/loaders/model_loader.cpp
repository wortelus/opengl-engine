// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  30/10/2023

#include <stdexcept>
#include "model_loader.h"

#include "../../../assets/bushes.h"
#include "../../../assets/gift.h"
#include "../../../assets/plain.h"
#include "../../../assets/sphere.h"
#include "../../../assets/suzi_flat.h"
#include "../../../assets/suzi_smooth.h"
#include "../../../assets/tree.h"
#include "../../../assets/triangle_tex.h"

ModelLoader::~ModelLoader() {
    for (auto& model : model_repository) {
        delete model.second;
    }
}

const Model* ModelLoader::loadModel(const char* name) {
    return this->loadModel(ModelKey{name, ModelOptions::NONE});
}

const Model* ModelLoader::loadModel(const ModelKey& model_key) {
    if (strcmp(model_key.name, "bushes") == 0) {
        return loadModel(model_key, bushes, sizeof(bushes));
    } else if (strcmp(model_key.name, "gift") == 0) {
        return loadModel(model_key, gift, sizeof(gift));
    } else if (strcmp(model_key.name, "plain") == 0) {
        return loadModel(model_key, plain, sizeof(plain));
    } else if (strcmp(model_key.name, "sphere") == 0) {
        return loadModel(model_key, sphere, sizeof(sphere));
    } else if (strcmp(model_key.name, "suzi_flat") == 0) {
        return loadModel(model_key, suziFlat, sizeof(suziFlat));
    } else if (strcmp(model_key.name, "suzi_smooth") == 0) {
        return loadModel(model_key, suziSmooth, sizeof(suziSmooth));
    } else if (strcmp(model_key.name, "tree") == 0) {
        return loadModel(model_key, tree, sizeof(tree));
    } else if (strcmp(model_key.name, "triangle_tex") == 0) {
            return loadModel(model_key, triangle, sizeof(triangle));
    } else {
        throw std::runtime_error("ModelLoader::loadModel: Unknown model name: " + std::string(model_key.name));
    }
}

const Model* ModelLoader::loadModel(const ModelKey& model_key, const float* vertices, const int& vertices_size) {
    auto it = model_repository.find(model_key);
    if (it == model_repository.end()) {
        auto* model = new Model(vertices, static_cast<int>(vertices_size / sizeof(float)), model_key.options);
        model_repository[model_key] = model; // copying ModelKey
        return model;
    }
    return it->second;
}
