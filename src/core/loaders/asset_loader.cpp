// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  19/11/2023

#include <stdexcept>
#include "asset_loader.h"

AssetLoader::~AssetLoader() {
    for (auto& model : model_repository) {
        delete model.second;
    }
}


const Asset* AssetLoader::loadAssetModel(const char* filename) {
    std::string path = std::string(ASSETS_PATH) + filename;
    auto it = model_repository.find(filename);
    if (it == model_repository.end()) {
        // load the file
        const aiScene* scene = importer.ReadFile(path.c_str(), importOptions);
        auto* asset = new Asset{readAssetModel(scene), readMaterial(scene)};

        model_repository[filename] = asset;
        return model_repository[filename];
    }
    return it->second;
}

Model AssetLoader::readAssetModel(const aiScene* scene) {
    if (!scene)
        throw std::runtime_error("ModelLoader::readAssetModel: " + std::string(importer.GetErrorString()));

    if (scene->mNumMeshes != 1)
        throw std::runtime_error("ModelLoader::readAssetModel: Only one mesh per file is supported");

    // read vertices, normals and texture uv's
    aiMesh* mesh = scene->mMeshes[0];
    auto data = std::vector<float>();
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];

        for (unsigned int j = 0; j < 3; j++)
        {
            int id = face.mIndices[j];

            //Vertex position
            aiVector3D pos = mesh->mVertices[id];
            data.push_back(pos.x);
            data.push_back(pos.y);
            data.push_back(pos.z);

            //Vertex normal
            aiVector3D nor = mesh->mNormals[id];
            data.push_back(nor.x);
            data.push_back(nor.y);
            data.push_back(nor.z);

            //Vertex uv
            aiVector3D uv = mesh->mTextureCoords[0][id];
            data.push_back(uv.x);
            data.push_back(uv.y);
        }
    }

    return Model(data.data(), static_cast<int>(data.size()), static_cast<ModelOptions>(ModelOptions::VERTICES | ModelOptions::NORMALS | ModelOptions::TEXTURED_UV));
}

Material AssetLoader::readMaterial(const aiScene* scene) {
    if (!scene)
        throw std::runtime_error("ModelLoader::readTexture: " + std::string(importer.GetErrorString()));

//    if (scene->mNumMaterials != 1)
//        throw std::runtime_error("ModelLoader::readTexture: Only one material per file is supported");

    aiMaterial* material = scene->mMaterials[0];
    aiColor3D color(0.f, 0.f, 0.f);
    Material m;

    // Ambient color
    if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_AMBIENT, color)) {
        m.ambient = glm::vec3(color.r, color.g, color.b);
    }

    // Diffuse color
    if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_DIFFUSE, color)) {
        glm::vec3 diffuseColor(color.r, color.g, color.b);
        m.diffuse = glm::vec3(color.r, color.g, color.b);
    }

    // Specular color
    if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_SPECULAR, color)) {
        glm::vec3 specularColor(color.r, color.g, color.b);
        m.specular = glm::vec3(color.r, color.g, color.b);
    }

    // Shininess float
    float f = 10.0f;
    if (AI_SUCCESS == aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &f)) {
        m.shininess = f;
    }

    return m;
}