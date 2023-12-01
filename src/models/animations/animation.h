// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  29/10/2023

#ifndef ZPG_ANIMATION_H
#define ZPG_ANIMATION_H

#include "../../util/observer.h"
#include "../../util/const.h"
#include "../drawable.h"

class Animation {
public:
    virtual ~Animation() = default;

    virtual void step(float delta_time) = 0;

    virtual void draw() = 0;

    virtual const SHADER_ALIAS_DATATYPE getShaderAlias() = 0;
    virtual void attachShader(IObserver* new_observer) = 0;
    virtual void notifyShader() = 0;

    virtual DrawableObject& getDrawableObject() = 0;
};

enum AnimationArgs {
    RESTART = (1u << 0u),
    CYCLE = (1u << 1u),
};


#endif //ZPG_ANIMATION_H
