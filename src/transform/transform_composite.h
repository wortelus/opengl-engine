// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  5/10/2023

#ifndef ZPG_TRANSFORM_COMPOSITE_H
#define ZPG_TRANSFORM_COMPOSITE_H

#include <vector>
#include <memory>
#include "transform.h"

class TransformComposite : public TransformationAbstract {
private:
    // composite components for the transformation
    std::unique_ptr<Translation> translation;
    std::unique_ptr<Rotation> rotation;
    std::unique_ptr<Scale> scale;

    // normal matrix
    // TODO: think about this
    std::shared_ptr<glm::mat3> normal_matrix;
public:
    TransformComposite();
    std::shared_ptr<glm::mat4> getMatrix() override;
    std::shared_ptr<glm::mat3> getNormalMatrix();
    void update(const EventArgs& event_args) override;
};

#endif //ZPG_TRANSFORM_COMPOSITE_H
