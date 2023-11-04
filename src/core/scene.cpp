// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  5/10/2023

//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>
#include <algorithm>
#include <utility>
#include <stdexcept>

//Include GLM
#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "glm/gtc/type_ptr.hpp" // glm::value_ptr

#include "scene.h"
#include "../../assets/sphere.h"
#include "../../assets/suzi_smooth.h"

Scene::Scene(const char& id, GLFWwindow& window_reference, const int& initial_width, const int& initial_height) :
        scene_id(id), window(&window_reference),
        last_x(initial_width / 2.0), last_y(initial_height / 2.0) {
    float ratio = (float) initial_width / (float) initial_height;
    this->camera = std::make_unique<Camera>(ratio);
    this->object_manager = std::make_unique<ObjectManager>();
    this->animation_manager = std::make_unique<AnimationManager>();
}

void Scene::init(std::shared_ptr<ShaderLoader> preloaded_shader_loader) {
    this->shader_loader = std::move(preloaded_shader_loader);

    // assign shader aliases
    for (const auto object: *object_manager) {
        assignShaderAlias(*object);
    }

    // assign shader aliases for animations
    for (const auto object: *animation_manager) {
        animation_manager->applyAnimations([this](Animation* object) {
            assignShaderAlias(object->getDrawableObject());
        });
    }

    // subscribe shaders to camera
    for (auto shader: *this->shader_loader) {
        camera->attach(shader);
    }

    // subscribe shaders to light manager
    for (auto shader: *this->shader_loader) {
        light_manager.attach(shader);
    }

    // subscribe single shader to drawable objects
    for (const auto object: *object_manager) {
        Shader* sh = this->shader_loader->loadShader(object->getShaderAlias());
        object->attach(sh);

        // make use of the loaded shader, and pre-pass uniforms just enough before the rendering loop
        object->notifyModel();
        object->notifyMaterial();
    }

    // subscribe single shader to drawable objects inside animations
    for (const auto animation: *animation_manager) {
        animation_manager->applyAnimations([this](Animation* animation) {
            Shader* sh = this->shader_loader->loadShader(animation->getShaderAlias());
            animation->attachShader(sh);
            animation->notifyShader();
        });
    }

    // pass camera and light uniforms to shaders
    camera->start();
    light_manager.notifyShaders();
}

void Scene::optimizeObjects() {
    object_manager->preprocess();
}

std::unique_ptr<DrawableObject> Scene::newObject(
        const Model* model_ptr,
        const glm::vec3 &position,
        const std::string &shader_name) {
    std::unique_ptr<DrawableObject> object = std::make_unique<DrawableObject>(position, model_ptr,
                                                                              shader_name, scene_ambient);
    return object;
}

std::unique_ptr<DrawableObject>Scene::newObject(
        const Model* model_ptr,
        const glm::vec3& position,
        const std::string& shader_name,
        const glm::vec3& axis) {
    std::unique_ptr<DrawableObject> object = std::make_unique<DrawableObject>(position, model_ptr,
                                                                              shader_name, scene_ambient, axis);
    return object;
}

DrawableObject& Scene::appendObject(
        const Model* model_ptr,
        const glm::vec3& position,
        const std::string& shader_name) {
    std::unique_ptr<DrawableObject> object = std::make_unique<DrawableObject>(position, model_ptr,
                                                                              shader_name, scene_ambient);
    auto& obj = object_manager->addObject(std::move(object));
    obj.setAmbient(scene_ambient);
    return obj;
}


void Scene::appendAnimation(const std::shared_ptr<Animation>& animation) {
    animation_manager->addAnimation(animation);
}

void Scene::appendLight(const Light& light) {
    light_manager.addLight(light);
}

void Scene::appendLight(const std::shared_ptr<Light>& light) {
    light_manager.addLight(light);
}


void Scene::run() {
    this->optimizeObjects();

    while (!is_finished) {

        auto current_frame_time = (float)glfwGetTime() * 300.0f;
        float delta_time = current_frame_time - last_frame_time;
        last_frame_time = current_frame_time;

        continuousMovement(delta_time);
        camera->jumpProgress(delta_time);

        // clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for (const auto object: *object_manager) {
            Shader* sh = shader_loader->loadShader(object->getShaderAlias());
            object->attach(sh);
            object->notifyModelParameters();
            sh->lazyPassUniforms();
            object->draw();
        }

        // animations
        for (const auto animation: *animation_manager) {
            animation_manager->applyAnimations([this, &delta_time](Animation* animation) {
                const SHADER_ALIAS_DATATYPE current_alias = animation->getShaderAlias();
                Shader* sh = shader_loader->loadShader(current_alias);
                animation->attachShader(sh);
                animation->step(delta_time);
                animation->notifyShader();
                sh->lazyPassUniforms();
                animation->draw();
            });
        }

        // update other events like input handling
        glfwPollEvents();
        // put the stuff we've been drawing onto the display
        glfwSwapBuffers(window);
    }
}

void Scene::handleKeyEventPress(int key, int scancode, int action, int mods) {
    switch (key) {
        case GLFW_MOUSE_BUTTON_RIGHT:
            right_mouse_button_pressed = true;
        case GLFW_KEY_SPACE:
            camera->jump();
            break;
            // components
        case GLFW_KEY_LEFT:
            object_manager->translate(glm::vec3(-0.1f, 0, 0));
            animation_manager->translate(glm::vec3(-0.1f, 0, 0));
            break;
        case GLFW_KEY_RIGHT:
            object_manager->translate(glm::vec3(0.1f, 0, 0));
            animation_manager->translate(glm::vec3(0.1f, 0, 0));
            break;
        case GLFW_KEY_UP:
            object_manager->translate(glm::vec3(0, 0.1f, 0));
            animation_manager->translate(glm::vec3(0, 0.1f, 0));
            break;
        case GLFW_KEY_DOWN:
            object_manager->translate(glm::vec3(0, -0.1f, 0));
            animation_manager->translate(glm::vec3(0, -0.1f, 0));
            break;
            // rotation along x-axis
        case GLFW_KEY_E:
            object_manager->rotate(glm::vec3(10.f, 0, 0));
            animation_manager->rotate(glm::vec3(10.f, 0, 0));
            break;
        case GLFW_KEY_F:
            object_manager->rotate(glm::vec3(-10.f, 0, 0));
            animation_manager->rotate(glm::vec3(-10.f, 0, 0));
            break;
            // rotation along y-axis
        case GLFW_KEY_R:
            object_manager->rotate(glm::vec3(0, 10.f, 0));
            animation_manager->rotate(glm::vec3(0, 10.f, 0));
            break;
        case GLFW_KEY_G:
            object_manager->rotate(glm::vec3(0, -10.f, 0));
            animation_manager->rotate(glm::vec3(0, -10.f, 0));
            break;
            // rotation along z-axis
        case GLFW_KEY_T:
            object_manager->rotate(glm::vec3(0, 0, 10.f));
            animation_manager->rotate(glm::vec3(0, 0, 10.f));
            break;
        case GLFW_KEY_H:
            object_manager->rotate(glm::vec3(0, 0, -10.f));
            animation_manager->rotate(glm::vec3(0, 0, -10.f));
            break;
            // scaling
        case GLFW_KEY_Z:
            object_manager->scale(glm::vec3(0.1f, 0.1f, 0.1f));
            animation_manager->scale(glm::vec3(0.1f, 0.1f, 0.1f));
            break;
        case GLFW_KEY_X:
            object_manager->scale(glm::vec3(-0.1f, -0.1f, -0.1f));
            animation_manager->scale(glm::vec3(-0.1f, -0.1f, -0.1f));
            break;
        default:
            break;
    }
}

void Scene::handleKeyEventRelease(int key, int scancode, int action, int mods) { }

Scene::~Scene() {}

void Scene::handleMouseMovementEvent(double x_pos, double y_pos) {
    if (!right_mouse_button_pressed)
        return;

    double x_offset = x_pos - last_x;
    double y_offset = last_y - y_pos;
    last_x = x_pos;
    last_y = y_pos;

    x_offset *= MOUSE_SENSITIVITY;
    y_offset *= MOUSE_SENSITIVITY;

    camera->move(x_offset, y_offset);
}

inline void Scene::continuousMovement(const float& delta_time) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->moveCharacterFront(CAMERA_SPEED * delta_time);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->moveCharacterFront(-CAMERA_SPEED * delta_time);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->moveCharacterSide(-CAMERA_SPEED * delta_time);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->moveCharacterSide(CAMERA_SPEED * delta_time);
}

void Scene::update_aspect_ratio(const int& new_width, const int& new_height) {
    camera->update_aspect_ratio(new_width, new_height);
}

void Scene::assignShaderAlias(DrawableObject& object) {
    if (int alias = shader_loader->getShaderAlias(object.getShaderName()); alias == SHADER_UNLOADED)
        throw std::runtime_error("Shader " + object.getShaderName() + " not loaded yet! Assigning shader alias failed.");
    else
        object.assignShaderAlias(alias);
}

void Scene::handleMouseButtonEventPress(int button, int action, int mods) {
    switch (button) {
        case GLFW_MOUSE_BUTTON_RIGHT:
            right_mouse_button_pressed = true;
            break;
        default:
            break;
    }
}

void Scene::handleMouseButtonEventRelease(int button, int action, int mods) {
    switch (button) {
        case GLFW_MOUSE_BUTTON_RIGHT:
            right_mouse_button_pressed = false;
            break;
        default:
            break;
    }
}
