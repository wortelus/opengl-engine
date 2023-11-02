// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  29/10/2023

#include "animation_manager.h"
#include "../models/animations/centric_model.h"

void AnimationManager::addAnimation(const std::shared_ptr<Animation>& animation) {
    animations.push_back(animation);
}

void AnimationManager::applyAnimations(const std::function<void(Animation*)>& func) {
    for (const auto& animation : animations) {
        // Check if it's a CentricComposite
        CentricComposite* composite = dynamic_cast<CentricComposite*>(animation.get());

        if (composite) {
            composite->bfsTraverse([func](CentricModelComponent* component) {
                // Note we are still using Animation*
                // CentricComposite is inheriting Animation virtual functions
                func(dynamic_cast<Animation*>(component));
            });
        } else {
            // If it's not a composite, apply the function directly.
            func(animation.get());
        }
    }
}

void AnimationManager::translate(const glm::vec3 &translation) {
    for(const auto& animation : animations) {
        animation->getDrawableObject().translate(translation);
    }
}

void AnimationManager::rotate(const glm::vec3 &axis_degrees) {
    for(const auto& animation : animations) {
        animation->getDrawableObject().rotate(axis_degrees);
    }
}

void AnimationManager::scale(const glm::vec3 &scale) {
    for(const auto& animation : animations) {
        animation->getDrawableObject().scale(scale);
    }
}
