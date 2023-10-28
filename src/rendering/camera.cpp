// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  9/10/2023

#include <algorithm>
#include <cstdio>
#include "camera.h"

Camera::Camera(float aspect) : aspect_ratio(aspect), position(CAMERA_POS), front(CAMERA_TARGET - CAMERA_POS),
                                                          pitch(CAMERA_PITCH), yaw(CAMERA_YAW) {
    view = glm::lookAt(CAMERA_POS, CAMERA_TARGET, CAMERA_UP);
    projection = glm::perspective(PROJECTION_FOV, aspect, PROJECTION_NEAR, PROJECTION_FAR);
}

void Camera::move(const double& x_offset, const double& y_offset) {
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

    view = glm::lookAt(position, position + front, up);

    notifyView();
}

void Camera::moveCharacterSide(const float& offset) {
    // cross product creates perpendicular vector, then we normalize it to length of 1
    glm::vec3 right = glm::normalize(glm::cross(front, CAMERA_UP));
    float y = position.y;
    position += right * offset;
    position.y = y;
    view = glm::lookAt(position, position + front, CAMERA_UP);

    notifyView();
    notifyPosition();
}

void Camera::moveCharacterFront(const float& offset) {
    float y = position.y;
    position += front * offset;
    position.y = y;
    view = glm::lookAt(position, position + front, CAMERA_UP);

    notifyView();
    notifyPosition();
}

void Camera::jumpProgress(const float& delta_time) {
    if(is_jumping) {
        current_jump_speed -= GRAVITY * delta_time;
        position.y += current_jump_speed * delta_time;

        // Check for landing
        if(position.y <= GROUND_LEVEL) {
            position.y = GROUND_LEVEL;
            current_jump_speed = 0;
            is_jumping = false;
        }
    }
    view = glm::lookAt(position, position + front, CAMERA_UP);

    notifyView();
    notifyPosition();
}

void Camera::jump() {
    if (!is_jumping && position.y == GROUND_LEVEL) {
        is_jumping = true;
        current_jump_speed = INITIAL_JUMP_VELOCITY;
    }
}

void Camera::update_aspect_ratio(const int& width, const int& height) {
    aspect_ratio = (float) width / (float) height;
    projection = glm::perspective(PROJECTION_FOV, aspect_ratio, PROJECTION_NEAR, PROJECTION_FAR);

    notifyProjection();
}

void Camera::notifyView() {
    EventPayload<glm::mat4> payload{view, EventType::U_VIEW_MATRIX};
    notify(payload);
}

void Camera::notifyProjection() {
    EventPayload<glm::mat4> payload{projection, EventType::U_PROJECTION_MATRIX};
    notify(payload);
}

void Camera::notifyPosition() {
    EventPayload<glm::vec3> payload{position, EventType::U_CAMERA_POSITION};
    notify(payload);
}

void Camera::notifyAll() {
    notifyView();
    notifyProjection();
    notifyPosition();
}

void Camera::start() {
    notifyAll();
}
