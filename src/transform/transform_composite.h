// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  5/10/2023

#ifndef ZPG_TRANSFORM_COMPOSITE_H
#define ZPG_TRANSFORM_COMPOSITE_H

#include <vector>
#include <memory>
#include "transform.h"

class INormal {
protected:
    glm::mat3 normal_matrix;
public:
    virtual const glm::mat3& getNormalMatrix() = 0;
};

class DynamicTransformComposite : public TransformationAbstract, INormal {
private:
    std::shared_ptr<TransformationAbstract> parent;
    std::vector<std::unique_ptr<TransformationAbstract>> components;
public:
    // default dynamic transform composite, no orbit rotation component
    DynamicTransformComposite();

    // default dynamic transform composite using origin
    // M=T×R_orbit×R_self×S
    explicit DynamicTransformComposite(const glm::vec3& axis);

    void setParent(std::shared_ptr<TransformationAbstract> component);

    const glm::mat4& getMatrix() override;
    const glm::mat3& getNormalMatrix() override;
    void update(const EventArgs& event_args) override;
};

#endif //ZPG_TRANSFORM_COMPOSITE_H
