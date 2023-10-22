// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  5/10/2023


#ifndef ZPG_SCENE_H
#define ZPG_SCENE_H

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


#include <memory>
#include <vector>
#include "../rendering/shader_loader.h"
#include "../models/drawable.h"
#include "../rendering/camera.h"
#include "../rendering/light/light.h"
#include "../rendering/light_manager.h"

class Scene {
private:
    GLFWwindow* window;
    ShaderLoader shaderLoader;

    std::vector<std::unique_ptr<DrawableObject>> objects;
    LightManager light_manager;

    std::unique_ptr<Camera> camera;

    const glm::vec3 scene_up = glm::vec3(0.0f, 1.0f, 0.0f);

    double last_x = 0.0;
    double last_y = 0.0;

    float last_frame_time = 0.0f;
public:
    explicit Scene(GLFWwindow& window_reference, const int& initial_width, const int& initial_height);
    ~Scene();

    void init();
    void createObjects();

    void run();

    inline void continuousMovement(const float& delta_time);

    void update_aspect_ratio(const int& new_width, const int& new_height);

    void handleKeyEventPress(int key, int scancode, int action, int mods);
    void handleMouseMovementEvent(double x_pos, double y_pos);
};


#endif //ZPG_SCENE_H
