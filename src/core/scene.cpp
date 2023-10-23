// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  5/10/2023

//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>
#include <algorithm>
#include <utility>

//Include GLM
#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/gtc/type_ptr.hpp" // glm::value_ptr

#include "scene.h"
#include "../../assets/sphere.h"
#include "../../assets/suzi_smooth.h"

Scene::Scene(const char &id, GLFWwindow &window_reference, const int &initial_width, const int &initial_height) :
        scene_id(id), window(&window_reference),
        last_x(initial_width / 2.0), last_y(initial_height / 2.0) {
    float ratio = (float) initial_width / (float) initial_height;
    this->camera = std::make_unique<Camera>(ratio);
    this->objects = std::vector<std::unique_ptr<DrawableObject>>();
}

void Scene::init(std::shared_ptr<ShaderLoader> shader_loader) {
    this->shaderLoader = std::move(shader_loader);
}

DrawableObject *
Scene::newObject(const float *vertices, const unsigned int &vertices_size, const glm::vec3 &position,
                 const std::string &shader_name) {
    std::unique_ptr<Model> model = std::make_unique<Model>(vertices, vertices_size / sizeof(float), 3, false);
    std::unique_ptr<DrawableObject> object = std::make_unique<DrawableObject>(position, std::move(model),
                                                                              shader_name);
    objects.push_back(std::move(object));
    return objects.back().get();
}

void Scene::appendLight(std::unique_ptr<Light> &&light) {
    light_manager.addLight(std::move(light));
}


void Scene::run() {
    while (!is_finished) {

//        auto current_frame_time = (float)glfwGetTime() * 300.0f;
//        float delta_time = current_frame_time - last_frame_time;
//        last_frame_time = current_frame_time;

        continuousMovement(1);
        camera->jumpProgress(1);

        // clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for (const auto &object: objects) {
            DrawableObject *d_obj = object.get();
            Shader *sh = shaderLoader->loadShader(d_obj->getShaderName());

            d_obj->passUniforms(sh);
            camera->passUniforms(sh);
            if (d_obj->isIlluminated())
                light_manager.passUniforms(sh);

            d_obj->draw();
        }

        // update other events like input handling
        glfwPollEvents();
        // put the stuff we've been drawing onto the display
        glfwSwapBuffers(window);
    }
}

void Scene::handleKeyEventPress(int key, int scancode, int action, int mods) {
    //
    // translations
    //
    if (key == GLFW_KEY_SPACE) {
        camera->jump();
    } else if (key == GLFW_KEY_LEFT) {
        for (const auto &object: objects) {
            object->move(glm::vec3(-0.1f, 0, 0));
        }
    } else if (key == GLFW_KEY_RIGHT) {
        for (const auto &object: objects) {
            object->move(glm::vec3(0.1f, 0, 0));
        }
    } else if (key == GLFW_KEY_UP) {
        for (const auto &object: objects) {
            object->move(glm::vec3(0, 0.1f, 0));
        }
    } else if (key == GLFW_KEY_DOWN) {
        for (const auto &object: objects) {
            object->move(glm::vec3(0, -0.1f, 0));
        }
    }
        //
        // rotation along x-axis
        //
    else if (key == GLFW_KEY_E) {
        for (const auto &object: objects) {
            object->rotate(glm::vec3(10.f, 0, 0));
        }
    } else if (key == GLFW_KEY_F) {
        for (const auto &object: objects) {
            object->rotate(glm::vec3(-10.f, 0, 0));
        }
    }
        //
        // rotation along y-axis
        //
    else if (key == GLFW_KEY_R) {
        for (const auto &object: objects) {
            object->rotate(glm::vec3(0, 10.f, 0));
        }
    } else if (key == GLFW_KEY_G) {
        for (const auto &object: objects) {
            object->rotate(glm::vec3(0, -10.f, 0));
        }
    }
        //
        // rotation along z-axis
        //
    else if (key == GLFW_KEY_T) {
        for (const auto &object: objects) {
            object->rotate(glm::vec3(0, 0, 10.f));
        }
    } else if (key == GLFW_KEY_H) {
        for (const auto &object: objects) {
            object->rotate(glm::vec3(0, 0, -10.f));
        }
    }
        //
        // scaling
        //
    else if (key == GLFW_KEY_Z) {
        for (const auto &object: objects) {
            object->scale(glm::vec3(0.1f, 0.1f, 0.1f));
        }
    } else if (key == GLFW_KEY_X) {
        for (const auto &object: objects) {
            object->scale(glm::vec3(-0.1f, -0.1f, -0.1f));
        }
    }
}

Scene::~Scene() {
    for (auto &object: objects) {
        object.reset();
    }
}

void Scene::handleMouseMovementEvent(double x_pos, double y_pos) {
    double x_offset = x_pos - last_x;
    double y_offset = last_y - y_pos;
    last_x = x_pos;
    last_y = y_pos;

    x_offset *= MOUSE_SENSITIVITY;
    y_offset *= MOUSE_SENSITIVITY;

    camera->move(x_offset, y_offset);
}

inline void Scene::continuousMovement(const float &delta_time) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->moveCharacterFront(CAMERA_SPEED * delta_time);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->moveCharacterFront(-CAMERA_SPEED * delta_time);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->moveCharacterSide(-CAMERA_SPEED * delta_time);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->moveCharacterSide(CAMERA_SPEED * delta_time);
}

void Scene::update_aspect_ratio(const int &new_width, const int &new_height) {
    camera->update_aspect_ratio(new_width, new_height);
}
