// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  9/10/2023

#include <algorithm>
#include "camera.h"

Camera::Camera(const int& init_width, const int& init_height) : width(init_width), height(init_height),
                                                                aspect_ratio(
                                                                        static_cast<float>(init_width) /
                                                                        static_cast<float>(init_height)),
                                                                position(CAMERA_POS), front(CAMERA_TARGET - CAMERA_POS),
                                                                pitch(CAMERA_PITCH), yaw(CAMERA_YAW) {
    mouse_x = width / 2.;
    mouse_y = height / 2.;

    view = glm::lookAt(CAMERA_POS, CAMERA_TARGET, CAMERA_UP);
    projection = glm::perspective(PROJECTION_FOV, aspect_ratio, PROJECTION_NEAR, PROJECTION_FAR);
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
    notifyFlashlight();
}

void Camera::moveCharacterSide(const float& offset) {
    glm::vec3 planar_front = glm::normalize(glm::vec3(front.x, 0.0f, front.z));

    // cross product creates perpendicular vector, then we normalize it to length of 1
    glm::vec3 right = glm::normalize(glm::cross(planar_front, CAMERA_UP));
    float y = position.y;
    position += right * offset * MOVEMENT_SENSITIVITY;
    position.y = y;
    view = glm::lookAt(position, position + front, CAMERA_UP);

    notifyView();
    notifyPosition();
    notifyFlashlight();
}

void Camera::moveCharacterFront(const float& offset) {
    glm::vec3 planar_front = glm::normalize(glm::vec3(front.x, 0.0f, front.z));

    float y = position.y;
    position += planar_front * offset * MOVEMENT_SENSITIVITY;
    position.y = y;
    view = glm::lookAt(position, position + front, CAMERA_UP);

    notifyView();
    notifyPosition();
    notifyFlashlight();
}

void Camera::jumpProgress(const float& delta_time) {
    if (is_jumping) {
        current_jump_speed -= GRAVITY * delta_time;
        position.y += current_jump_speed * delta_time;

        // Check for landing
        if (position.y <= GROUND_LEVEL) {
            position.y = GROUND_LEVEL;
            current_jump_speed = 0;
            is_jumping = false;
        }
    }
    view = glm::lookAt(position, position + front, CAMERA_UP);

    notifyView();
    notifyPosition();
    notifyFlashlight();
}

void Camera::jump() {
    if (!is_jumping && position.y == GROUND_LEVEL) {
        is_jumping = true;
        current_jump_speed = INITIAL_JUMP_VELOCITY;
    }
}

void Camera::update_aspect_ratio(const int& _width, const int& _height) {
    this->width = _width;
    this->height = _height;
    aspect_ratio = (float) _width / (float) _height;
    projection = glm::perspective(PROJECTION_FOV, aspect_ratio, PROJECTION_NEAR, PROJECTION_FAR);

    notifyProjection();
}

void Camera::notifyView() {
    EventPayload<const glm::mat4&> payload{view, EventType::U_VIEW_MATRIX};
    notify(payload);
}

void Camera::notifyProjection() {
    EventPayload<const glm::mat4&> payload{projection, EventType::U_PROJECTION_MATRIX};
    notify(payload);
}

void Camera::notifyPosition() {
    EventPayload<const glm::vec3&> payload{position, EventType::U_CAMERA_POSITION};
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

void Camera::notifyFlashlight() {
    auto flashlight_ptr = flashlight.lock();

    flashlight_ptr->setPosition(position);
    flashlight_ptr->setDirection(front);

    EventPayload<LIGHT_ID> payload{flashlight_ptr->getManagedId(), EventType::U_LIGHT_SINGLE};
    notify(payload);
}

void Camera::setFlashlight(const std::weak_ptr<Spotlight>& weak_flashlight) {
    this->flashlight = weak_flashlight;
}

glm::vec4 Camera::getColorBuffer(double x_ps, double y_pos) const {
    auto x = static_cast<GLint>(x_ps);
    auto y = static_cast<GLint>(y_pos);
    int new_y = this->getHeight() - y;
    unsigned char data[4];
    glReadPixels(x, new_y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
    return {data[0], data[1], data[2], data[3]};
}

float Camera::getDepthBuffer(double x_pos, double y_pos) const {
    auto x = static_cast<GLint>(x_pos);
    auto y = static_cast<GLint>(y_pos);
    int new_y = this->getHeight() - y;
    float data;
    glReadPixels(x, new_y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &data);
    return data;
}

char Camera::getStencilBuffer(double x_pos, double y_pos) const {
    auto x = static_cast<GLint>(x_pos);
    auto y = static_cast<GLint>(y_pos);
    int new_y = this->getHeight() - y;
    char data;
    glReadPixels(x, new_y, 1, 1, GL_STENCIL_INDEX, GL_BYTE, &data);
    return data;
}

glm::vec3 Camera::getWorldPosition(double x_pos, double y_pos, float depth) const {
    auto x = static_cast<GLint>(x_pos);
    auto y = static_cast<GLint>(y_pos);
    int new_y = this->getHeight() - y;

    glm::vec3 screenX = glm::vec3(x, new_y, depth);
    glm::vec4 viewPort = glm::vec4(0, 0, this->getWidth(), this->getHeight());
    return glm::unProject(screenX, this->getView(), this->getProjection(), viewPort);
}