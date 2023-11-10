// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  6/11/2023

#include "texture_loader.h"
#include <SOIL/SOIL.h>
#include <array>
#include <stdexcept>

TextureLoader::~TextureLoader() {
    for (auto const& texture: texture_repository) {
        delete texture.second;
    }
}


const Texture* TextureLoader::loadTexture(const char* name) {
    std::string path = std::string(ASSETS_PATH) + name;
    auto it = texture_repository.find(name);
    if (it == texture_repository.end()) {
        TEXTURE_ID tex_id = SOIL_load_OGL_texture(path.c_str(),
                                                  SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
        if (tex_id == 0) {
            throw std::runtime_error("TextureLoader::loadTexture: Failed to load texture: " + std::string(name));
        }
        auto* tex = new Texture(tex_id);
        texture_repository.insert(std::pair<std::string, Texture*>(name, tex));
        return tex;
    }
    return it->second;
}

const Texture* TextureLoader::loadCubeMap(const char* name, const char* extension) {
    std::string path = std::string(ASSETS_PATH) + name;
    std::array<std::string, 6> skybox_texture_names = {
            path + "_px" + extension,
            path + "_nx" + extension,
            path + "_py" + extension,
            path + "_ny" + extension,
            path + "_pz" + extension,
            path + "_nz" + extension
    };
    auto it = texture_repository.find(name);
    if (it == texture_repository.end()) {
        TEXTURE_ID tex_id = SOIL_load_OGL_cubemap(
                skybox_texture_names[0].c_str(), skybox_texture_names[1].c_str(),
                skybox_texture_names[2].c_str(), skybox_texture_names[3].c_str(),
                skybox_texture_names[4].c_str(), skybox_texture_names[5].c_str(),
                SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);
        if (tex_id == 0) {
            throw std::runtime_error("TextureLoader::loadCubeMap: Failed to load cube map at: " + path);
        }
        auto* tex = new Texture(tex_id);
        texture_repository.insert(std::pair<std::string, Texture*>(name, tex));
        return tex;
    }
    return it->second;
}
