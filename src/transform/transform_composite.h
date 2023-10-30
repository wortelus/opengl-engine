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
    std::shared_ptr<glm::mat3> normal_matrix;
public:
    virtual std::shared_ptr<glm::mat3> getNormalMatrix() = 0;
};

class [[maybe_unused]] TransformComposite : public TransformationAbstract, INormal {
private:
    // composite components for the transformation
    std::unique_ptr<Translation> translation;
    std::unique_ptr<Rotation> rotation;
    std::unique_ptr<Scale> scale;
public:
    TransformComposite();

    std::shared_ptr<glm::mat4> getMatrix() override;
    std::shared_ptr<glm::mat3> getNormalMatrix() override;

    void update(const EventArgs& event_args) override;
};

class DynamicTransformComposite : public TransformationAbstract, INormal {
private:
    std::vector<std::unique_ptr<TransformationAbstract>> components;
public:
    // default dynamic transform composite, no orbit rotation component
    DynamicTransformComposite();

    // default dynamic transform composite using origin
    // M=T×R_orbit×R_self×S
    explicit DynamicTransformComposite(const glm::vec3& axis);

    // explicit dynamic transform composite -> appends rotation along origin
    explicit DynamicTransformComposite(std::vector<std::unique_ptr<TransformationAbstract>> components);

    std::shared_ptr<glm::mat4> getMatrix() override;
    std::shared_ptr<glm::mat3> getNormalMatrix() override;
    void update(const EventArgs& event_args) override;
};

#endif //ZPG_TRANSFORM_COMPOSITE_H
