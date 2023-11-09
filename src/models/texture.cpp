// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  6/11/2023

#include <GL/glew.h>
#include "texture.h"

Texture::Texture(const TEXTURE_ID id) : texture_id(id), texture_unit(GL_TEXTURE0) { }

Texture::Texture(const TEXTURE_ID id, const GLenum unit) : texture_id(id), texture_unit(unit) {
    glBindTexture(texture_unit, texture_id);
    glTexParameteri(texture_unit, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texture_unit, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(texture_unit, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(texture_unit, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::bind() const {
    glActiveTexture(texture_unit);
    glBindTexture(GL_TEXTURE_2D, texture_id);
}
