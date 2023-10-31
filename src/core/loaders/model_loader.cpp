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

ModelLoader::~ModelLoader() {
    for (auto& model : model_repository) {
        delete model.second;
    }
}

const Model* ModelLoader::loadModel(const std::string &name) {
    if (name == "bushes") {
        return loadModel(name, bushes, sizeof(bushes));
    } else if (name == "gift") {
        return loadModel(name, gift, sizeof(gift));
    } else if (name == "plain") {
        return loadModel(name, plain, sizeof(plain));
    } else if (name == "sphere") {
        return loadModel(name, sphere, sizeof(sphere));
    } else if (name == "suzi_flat") {
        return loadModel(name, suziFlat, sizeof(suziFlat));
    } else if (name == "suzi_smooth") {
        return loadModel(name, suziSmooth, sizeof(suziSmooth));
    } else if (name == "tree") {
        return loadModel(name, tree, sizeof(tree));
    } else {
        throw std::runtime_error("ModelLoader::loadModel: Unknown model name: " + name);
    }
}

const Model* ModelLoader::loadModel(const std::string &name, const float *vertices, const int &vertices_size) {
    auto it = model_repository.find(name);
    if (it == model_repository.end()) {
        auto* model = new Model(vertices, static_cast<int>(vertices_size / sizeof(float)));
        model_repository[name] = model;
        return model;
    }
    return it->second;
}
