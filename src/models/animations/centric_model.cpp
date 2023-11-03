// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  29/10/2023

#include "centric_model.h"

void CentricModelComponent::step(float delta_time) {
    float angle_increment = delta_time * rotational_multiplier;
    object->rotateAround(angle_increment, parent_center);
}

void CentricComposite::addModel(std::unique_ptr<CentricModelComponent> model) {
    // Append the current model's matrix to the child's matrix
    // setModelParent creates a weak_ptr to the parent's matrix
    model->getDrawableObject().setModelParent(object->getModelComposite());

    // set the rotation center to the child's position
    // it is based on initial position of model as a relative position to the parent
    auto rot_center = -model->getDrawableObject().getPosition();
    model->setCenter(rot_center);

    // append the child to the children vector
    children.push_back(std::move(model));
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
