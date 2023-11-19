// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  19/11/2023

#ifndef ZPG_ASSET_LOADER_H
#define ZPG_ASSET_LOADER_H

#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>

#include <map>

#include "../../models/model.h"
#include "../../models/properties/material.h"

static constexpr unsigned int importOptions = aiProcess_Triangulate
                                              | aiProcess_OptimizeMeshes              // reduce the number of draw calls
                                              | aiProcess_JoinIdenticalVertices       // identifies and joins identical vertex data sets within all imported meshes
                                              | aiProcess_Triangulate                 // triangulates all faces of all meshes
                                              | aiProcess_CalcTangentSpace;           // calculates the tangents and bitangents for the imported meshes

struct Asset {
    const Model model;
    const Material material;
};

class AssetLoader {
private:
    Assimp::Importer importer;
    std::map<const char*, Asset*> model_repository;

    // Private constructor to prevent instantiation
    AssetLoader() { }
    ~AssetLoader();

private:
    Model readAssetModel(const aiScene* scene);
    Material readMaterial(const aiScene* scene);
public:
    AssetLoader(AssetLoader const&) = delete;
    void operator=(AssetLoader const&) = delete;

    // Singleton
    static AssetLoader& getInstance() {
        static AssetLoader instance;
        return instance;
    }


    const Asset* loadAssetModel(const char* filename);
};


#endif //ZPG_ASSET_LOADER_H
