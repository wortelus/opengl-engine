// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  29/10/2023

#include "centric_model.h"

void CentricModelComponent::step(float delta_time) {
    glm::vec3 relative_position = object->getPosition() - parent_center;

    float angle_increment = delta_time * rotational_multiplier;
    glm::vec3 earth_position = glm::vec3(-2,0,0);
    object->rotateAround(angle_increment, earth_position);
}

void CentricComposite::addModel(std::shared_ptr<CentricModelComponent> model) {
    model->getDrawableObject().setModelParent(object->getModelComposite());
    children.push_back(std::move(model));
}

void CentricComposite::step(float delta_time) {
    for (const auto& child: children) {
        child->setCenter(object->getModelMatrix() * glm::vec4(0,0,0,1));
    }

    float angle_increment = delta_time * rotational_multiplier;
    glm::vec3 sun_position = glm::vec3(-4,0,0);
    object->rotateAround(angle_increment, sun_position);
}

void CentricComposite::bfsTraverse(const std::function<void(CentricModelComponent *)> &func) {
    std::queue<CentricModelComponent*> bfs_queue;
    bfs_queue.push(this);

    while (!bfs_queue.empty()) {
        CentricModelComponent* current = bfs_queue.front();
        bfs_queue.pop();

        func(current);

        auto* composite = dynamic_cast<CentricComposite*>(current);
        if (composite) {
            for (const auto& child: composite->children) {
                bfs_queue.push(child.get());
            }
        }
    }
}
