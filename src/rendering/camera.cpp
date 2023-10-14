// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  9/10/2023

#include <algorithm>
#include "camera.h"
#include "../util/const.h"

Camera::Camera(float aspect) : front(CAMERA_TARGET - CAMERA_POS), pitch(CAMERA_PITCH), yaw(CAMERA_YAW) {
    view = glm::lookAt(CAMERA_POS, CAMERA_TARGET, CAMERA_UP);
    projection = glm::perspective(PROJECTION_FOV, aspect, PROJECTION_NEAR, PROJECTION_FAR);
}

void Camera::move(double x_offset, double y_offset) {
    yaw += x_offset;
    pitch += y_offset;

    // Ensure that the camera pitch isn't flipped over
    pitch = std::clamp(pitch, -89.0, 89.0);

    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    auto right = glm::normalize(glm::cross(front, CAMERA_UP));
    auto up = glm::normalize(glm::cross(right, front));

    view = glm::lookAt(CAMERA_POS, CAMERA_POS + front, up);
}
