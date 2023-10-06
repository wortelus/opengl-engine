//
// Created by wortelus on 5.10.23.
//

#ifndef ZPG_TRANSFORM_COMPOSITE_H
#define ZPG_TRANSFORM_COMPOSITE_H

#include <vector>
#include <memory>
#include "transform.h"

class TransformComposite : public TransformationAbstract {
private:
    std::unique_ptr<Translation> translation;
    std::unique_ptr<Rotation> rotation;
    std::unique_ptr<Scale> scale;

    // model matrix cache
    std::unique_ptr<glm::mat4> model_matrix;
    bool is_dirty = false;
public:
    TransformComposite();
    const glm::mat4& GetMatrix() override;
    void Update(const EventArgs& event_args) override;
};


#endif //ZPG_TRANSFORM_COMPOSITE_H
