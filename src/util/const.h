// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  12/10/2023

#ifndef ZPG_CONST_H
#define ZPG_CONST_H

#include <GL/glew.h>
#include "glm/vec3.hpp"
#include "glm/trigonometric.hpp"

using SHADER_ALIAS_DATATYPE = int;
using SHADER_UNIFORM_LOCATION = GLint;

inline constexpr bool ENABLE_CULL_FACE = true;
inline constexpr bool DISABLE_VSYNC = false;

inline constexpr SHADER_ALIAS_DATATYPE SHADER_UNLOADED = (-1);

const char* const SHADERS_PATH = "shaders";

inline constexpr char DEFAULT_SCENE = 0;

inline constexpr glm::vec3 AMBIENT_LIGHT = glm::vec3(0.05f, 0.05f, 0.05f);

// Mouse sensitivity for camera movement
inline constexpr float MOVEMENT_SENSITIVITY = 0.5f;
inline constexpr float MOUSE_SENSITIVITY = 0.5f;
inline constexpr bool DISABLE_CURSOR = false;

// Movement speed for camera movement
inline constexpr float CAMERA_SPEED = 0.1f;

// Jumping
inline constexpr float INITIAL_JUMP_VELOCITY = 0.25;
inline constexpr float GRAVITY = 0.0025;
inline constexpr float GROUND_LEVEL = 2.0;

// Initial camera position
inline constexpr glm::vec3 CAMERA_POS = glm::vec3(0.0f, GROUND_LEVEL, 3.0f);
// Looking at the origin
inline constexpr glm::vec3 CAMERA_TARGET = glm::vec3(0.0f, GROUND_LEVEL, 0.0f);
// Up vector for the camera
inline constexpr glm::vec3 CAMERA_UP = glm::vec3(0.0f, GROUND_LEVEL + 1.0f, 0.0f);

// Initial camera yaw
// -90.0 degrees
inline constexpr float CAMERA_YAW = -90.0f;
// Initial camera pitch
inline constexpr float CAMERA_PITCH = 0.0f;

// Projection FOV (field of view)
inline constexpr float PROJECTION_FOV = glm::radians(45.0f);
// Projection near clipping distance
inline constexpr float PROJECTION_NEAR = 0.1f;
// Projection max far clipping distance
inline constexpr float PROJECTION_FAR = 1000.0f;


#endif //ZPG_CONST_H
