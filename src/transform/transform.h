// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  2/10/2023

#ifndef ZPG_TRANSFORM_H
#define ZPG_TRANSFORM_H


#include <memory>
#include "glm/ext/matrix_float4x4.hpp"
#include "../util/observer.h"

class TransformationAbstract : public IObserver {
protected:
    const float default_w = 1.0f;
    std::shared_ptr<glm::mat4> matrix;
    bool is_dirty = false;
public:
    virtual std::shared_ptr<glm::mat4> getMatrix() = 0;
};

class Translation : public TransformationAbstract {
private:
    glm::vec3 translation;
public:
    explicit Translation(const glm::vec3& translation);

    void setTranslation(const glm::vec3& translation);
    void moveBy(const glm::vec3& offset);

    void update(const EventArgs& event_args) override;
    std::shared_ptr<glm::mat4> getMatrix() override;
};

class Rotation : public TransformationAbstract {
private:
    glm::vec3 origin; // TODO: remove this
    glm::vec3 rotation;
public:
    Rotation();
    explicit Rotation(const glm::vec3& origin);

    void rotateBy(const glm::vec3& offset);
    void setRotation(const glm::vec3& rotation);

    void update(const EventArgs& event_args) override;
    std::shared_ptr<glm::mat4> getMatrix() override;
};

class Scale : public TransformationAbstract {
private:
    glm::vec3 scale;
public:
    explicit Scale(const glm::vec3& scale);

    void scaleBy(const glm::vec3& offset);
    void setScale(const glm::vec3& scale);

    void update(const EventArgs& event_args) override;
    std::shared_ptr<glm::mat4> getMatrix() override;
};

class RotationPoint : public TransformationAbstract {
private:
    glm::vec3 origin;
    glm::vec3 axis;
    float angle = 0.f;
public:
    explicit RotationPoint(const glm::vec3& rot_axis);
    RotationPoint(const glm::vec3& rot_axis, const glm::vec3& initial_origin);

    void setAxis(const glm::vec3& new_axis);
    void setOrigin(const glm::vec3& new_origin);

    void rotateBy(const float& offset);
    void setRotation(const float& new_rotation);

    void update(const EventArgs& event_args) override;
    std::shared_ptr<glm::mat4> getMatrix() override;
};


#endif //ZPG_TRANSFORM_H
