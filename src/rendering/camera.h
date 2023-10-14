// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  9/10/2023

#ifndef ZPG_CAMERA_H
#define ZPG_CAMERA_H

//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>

//Include GLM
#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/gtc/type_ptr.hpp" // glm::value_ptr

#include "../util/const.h"

class Camera {
private:
    glm::vec3 front;
    glm::mat4 view;
    glm::mat4 projection;

    double yaw = 0;
    double pitch = 0;
public:
    explicit Camera(float aspect);
    void move(double x_offset, double y_offset);

    [[nodiscard]] const glm::mat4& getView() const { return view; }
    [[nodiscard]] const glm::mat4& getProjection() const { return projection; }
};


#endif //ZPG_CAMERA_H
