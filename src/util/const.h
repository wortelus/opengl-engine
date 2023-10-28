// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  12/10/2023

#ifndef ZPG_CONST_H
#define ZPG_CONST_H

#include "glm/vec3.hpp"
#include "glm/trigonometric.hpp"

const bool DISABLE_VSYNC = true;

#define SHADER_ALIAS_DATATYPE int
#define SHADER_UNLOADED (-1)

const char* const ASSETS_PATH = "assets";
const char* const SHADERS_PATH = "shaders";

const char DEFAULT_SCENE = 0;

const glm::vec3 OBJECT_COLOR = glm::vec3(1.0f, 1.0f, 1.0f);
const glm::vec3 AMBIENT_LIGHT = glm::vec3(0.05f, 0.05f, 0.05f);

// Mouse sensitivity for camera movement
const float MOVEMENT_SENSITIVITY = 0.25;
const double MOUSE_SENSITIVITY = 0.1;
const bool DISABLE_CURSOR = false;

// Movement speed for camera movement
const float CAMERA_SPEED = 0.1;

// Jumping
const float INITIAL_JUMP_VELOCITY = 0.25;
const float GRAVITY = 0.025;
const float GROUND_LEVEL = 2.0;

// Initial camera position
const glm::vec3 CAMERA_POS = glm::vec3(0.0f, GROUND_LEVEL, 3.0f);
// Looking at the origin
const glm::vec3 CAMERA_TARGET = glm::vec3(0.0f, GROUND_LEVEL, 0.0f);
// Up vector for the camera
const glm::vec3 CAMERA_UP = glm::vec3(0.0f, GROUND_LEVEL + 1.0f, 0.0f);

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
