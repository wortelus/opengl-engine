// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  29/10/2023

#include "centric_model.h"

void CentricModelComponent::step(float delta_time) {
    glm::vec4 local_position = glm::vec4(object->getPosition(), 1.0f);
    glm::vec4 world_position = local_position; // TODO: add model matrix after it starts working
    glm::vec3 world_space_root_position = glm::vec3(world_position);

    object->rotateAround(delta_time * rotational_multiplier, parent_center - world_space_root_position);
}

void CentricComposite::addModel(std::shared_ptr<CentricModelComponent> model) {
    models.push_back(std::move(model));
}

void CentricComposite::step(float delta_time) {
    glm::vec4 local_position = glm::vec4(object->getPosition(), 1.0f);
    glm::vec4 world_position = local_position; // TODO: add model matrix after it starts working
    glm::vec3 world_space_root_position = glm::vec3(world_position);

    object->rotateAround(delta_time * rotational_multiplier, parent_center - world_space_root_position);

    world_space_root_position = glm::vec3(*object->getModelMatrix() * local_position);

    for (auto& model: models) {
        model->setCenter(world_space_root_position);
    }
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
            for (const auto& child: composite->models) {
                bfs_queue.push(child.get());
            }
        }
    }
}
