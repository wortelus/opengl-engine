// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  6/11/2023

#include <GL/glew.h>
#include "texture.h"

Texture::Texture(const TEXTURE_ID id) : texture_id(id), texture_unit(GL_TEXTURE0), target(GL_TEXTURE_2D) {
    glBindTexture(target, texture_id);
    glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::Texture(const TEXTURE_ID id, const GLenum unit) : texture_id(id), texture_unit(unit), target(GL_TEXTURE_2D) {
    glBindTexture(target, texture_id);
    glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::Texture(TEXTURE_ID id, GLenum unit, TEXTURE_TARGET bind_target) : texture_id(id), texture_unit(unit), target(bind_target) {
    glBindTexture(bind_target, id);
    glTexParameteri(bind_target, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(bind_target, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(bind_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(bind_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}

void Texture::bind() const {
    glActiveTexture(texture_unit);
    glBindTexture(target, texture_id);
}
