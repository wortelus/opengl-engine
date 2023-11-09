// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  6/11/2023

#ifndef ZPG_TEXTURE_H
#define ZPG_TEXTURE_H

#include "../../util/const.h"

class Texture {
private:
    const TEXTURE_ID texture_id;
    const GLenum texture_unit;
public:
    explicit Texture(TEXTURE_ID id);
    explicit Texture(TEXTURE_ID id, GLenum unit);

    [[nodiscard]] TEXTURE_ID getTextureId() const { return texture_id; }

    void bind() const;
};


#endif //ZPG_TEXTURE_H
