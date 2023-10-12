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

class Scene {
private:
    GLFWwindow* window;
    ShaderLoader shaderLoader;
    std::vector<std::unique_ptr<DrawableObject>> objects;

    std::unique_ptr<Camera> camera;

    const int width;
    const int height;
public:
    explicit Scene(GLFWwindow& window_reference, int initial_width, int initial_height);
    ~Scene();

    void init();
    void createObjects();

    void run();

    void handleKeyEvent(int key, int scancode, int action, int mods);
};


#endif //ZPG_SCENE_H
