//
// Created by wortelus on 30.10.23.
//

#ifndef ZPG_MODEL_LOADER_H
#define ZPG_MODEL_LOADER_H


#include <memory>
#include <map>
#include "../models/model.h"

class ModelLoader {
private:
    std::map<std::string, Model*> model_repository;

    // Private constructor to prevent instantiation
    ModelLoader() { }
    ~ModelLoader();

private:
    const Model* loadModel(const std::string& name, const float* vertices, const int& vertices_size);
public:
    ModelLoader(ModelLoader const&) = delete;
    void operator=(ModelLoader const&) = delete;

    // Singleton
    static ModelLoader& getInstance() {
        static ModelLoader instance;
        return instance;
    }

    const Model* loadModel(const std::string& name);
};



#endif //ZPG_MODEL_LOADER_H
