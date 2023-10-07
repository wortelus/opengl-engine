// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  2/10/2023

#ifndef ZPG_TRANSFORM_H
#define ZPG_TRANSFORM_H


#include "glm/ext/matrix_float4x4.hpp"
#include "observer.h"

class TransformationAbstract : public IObserver {
protected:
    const float default_w = 1.0f;
    // TODO: unique_ptr?
    glm::mat4 matrix;
public:
    virtual const glm::mat4& getMatrix() = 0;
};

class Translation : public TransformationAbstract {
private:
    glm::vec3 translation;
public:
    explicit Translation(const glm::vec3 &translation);

    void setTranslation(const glm::vec3 &translation);
    void moveBy(const glm::vec3 &translation);

    void update(const EventArgs &event_args) override;
    const glm::mat4& getMatrix() override;
};

class Rotation : public TransformationAbstract {
private:
    glm::vec3 origin;
    glm::vec3 rotation;
public:
    Rotation();
    explicit Rotation(const glm::vec3 &origin);

    void rotateBy(const glm::vec3 &rotation);
    void setRotation(const glm::vec3 &rotation);

    void update(const EventArgs &event_args) override;
    const glm::mat4& getMatrix() override;
};

class Scale : public TransformationAbstract {
private:
    glm::vec3 scale;
public:
    explicit Scale(const glm::vec3 &scale);

    void setScale(const glm::vec3 &scale);
    void scaleBy(const glm::vec3 &scale);

    void update(const EventArgs &event_args) override;
    const glm::mat4& getMatrix() override;
};




#endif //ZPG_TRANSFORM_H
