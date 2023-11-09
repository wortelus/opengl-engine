// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  6/11/2023

#include "texture_loader.h"
#include <SOIL/SOIL.h>

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
        auto* tex = new Texture(tex_id);
        texture_repository.insert(std::pair<std::string, Texture*>(name, tex));
        return tex;
    }
    return it->second;
}
