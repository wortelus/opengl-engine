// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  6/11/2023

#ifndef ZPG_TEXTURE_LOADER_H
#define ZPG_TEXTURE_LOADER_H


#include <string>
#include <map>
#include "../../models/properties/texture.h"

class TextureLoader {
private:
    std::map<std::string, Texture*> texture_repository;

    // Private constructor to prevent instantiation
    TextureLoader() { }
    ~TextureLoader();

public:
    TextureLoader(TextureLoader const&) = delete;
    void operator=(TextureLoader const&) = delete;

    // Singleton
    static TextureLoader& getInstance() {
        static TextureLoader instance;
        return instance;
    }

    const Texture* loadTexture(const char* name);
};

#endif //ZPG_TEXTURE_LOADER_H
