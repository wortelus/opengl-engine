// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  30/10/2023

#ifndef ZPG_MODEL_LOADER_H
#define ZPG_MODEL_LOADER_H


#include <memory>
#include <map>
#include "../../models/model.h"

struct ModelKey {
    const char* name;
    ModelOptions options;

    ModelKey(const char* name, ModelOptions options) : name(name), options(options) { }

    // used for std::map find()
    bool operator<(const ModelKey& other) const {
        int cmp = strcmp(name, other.name);
        if (cmp != 0) return cmp < 0;
        return options < other.options;
    }
};

class ModelLoader {
private:
    std::map<ModelKey, Model*> model_repository;

    // Private constructor to prevent instantiation
    ModelLoader() { }
    ~ModelLoader();

private:
    const Model* loadModel(const ModelKey& model_key, const float* vertices, const int& vertices_size);
public:
    ModelLoader(ModelLoader const&) = delete;
    void operator=(ModelLoader const&) = delete;

    // Singleton
    static ModelLoader& getInstance() {
        static ModelLoader instance;
        return instance;
    }

    const Model* loadModel(const std::string& name);
    const Model* loadModel(const ModelKey& model_key);
};



#endif //ZPG_MODEL_LOADER_H
