// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  6/11/2023

#include <GL/glew.h>
#include "texture.h"

void Texture::load() {
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glActiveTexture(GL_TEXTURE0);

    // set the texture wrapping/filtering options (on the currently bound texture object)
}

Texture::Texture(const TEXTURE_ID id) : texture_id(id), unit(GL_TEXTURE0) { }

Texture::Texture(const TEXTURE_ID id, const GLenum type) : texture_id(id), unit(type) {
    glBindTexture(type, texture_id);
    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::bind() const {
    glActiveTexture(unit);
    glBindTexture(GL_TEXTURE_2D, texture_id);
}
