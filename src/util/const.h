// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  12/10/2023

#ifndef ZPG_CONST_H
#define ZPG_CONST_H

#include "glm/vec3.hpp"
#include "glm/trigonometric.hpp"


// Mouse sensitivity for camera movement
const double MOUSE_SENSITIVITY = 0.1;

// Initial camera position
const glm::vec3 CAMERA_POS = glm::vec3(0.0f, 0.0f, 3.0f);
// Looking at the origin
const glm::vec3 CAMERA_TARGET = glm::vec3(0.0f, 0.0f, 0.0f);
// Up vector for the camera
const glm::vec3 CAMERA_UP = glm::vec3(0.0f, 1.0f, 0.0f);

// Initial camera yaw
// -90.0 degre
const float CAMERA_YAW = -90.0f;
// Initial camera pitch
const float CAMERA_PITCH = 0.0f;

// Projection FOV (field of view)
const float PROJECTION_FOV = glm::radians(45.0f);
// Projection near clipping distance
const float PROJECTION_NEAR = 0.1f;
// Projection max far clipping distance
const float PROJECTION_FAR = 100.0f;




#endif //ZPG_CONST_H
