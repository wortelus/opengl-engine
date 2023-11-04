// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  9/10/2023

#ifndef ZPG_CAMERA_H
#define ZPG_CAMERA_H

//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>
#include <vector>
#include <memory>

//Include GLM
#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/gtc/type_ptr.hpp" // glm::value_ptr

#include "../util/const.h"
#include "../util/observer.h"
#include "light/spotlight.h"

class Camera : public ISubject {
private:
    glm::vec3 position;

    glm::vec3 front;
    glm::mat4 view;
    glm::mat4 projection;

    double yaw = 0;
    double pitch = 0;

    bool is_jumping = false;
    float current_jump_speed = 0;

    float aspect_ratio;

    std::weak_ptr<Spotlight> flashlight;
private:
    void notifyAll();

    void notifyView();
    void notifyProjection();
    void notifyPosition();
    void notifyFlashlight();
public:
    explicit Camera(float aspect);

    void start();

    void setFlashlight(const std::weak_ptr<Spotlight>& weak_flashlight);

    void update_aspect_ratio(const int& width, const int& height);

    void move(const double& x_offset, const double& y_offset);
    void moveCharacterSide(const float& offset);
    void moveCharacterFront(const float& offset);
    void jump();
    void jumpProgress(const float& delta_time);

    [[nodiscard]] bool isJumping() const { return is_jumping; }
    [[nodiscard]] const glm::mat4& getView() const { return view; }
    [[nodiscard]] const glm::mat4& getProjection() const { return projection; }
    [[nodiscard]] const glm::vec3& getPosition() const { return position; }
};


#endif //ZPG_CAMERA_H
