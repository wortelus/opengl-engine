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
#include "loaders/model_loader.h"

Scene::Scene(const char& id, GLFWwindow& window_reference, const int& initial_width, const int& initial_height) :
        scene_id(id), window(&window_reference) {
    this->camera = std::make_unique<Camera>(initial_width, initial_height);
    this->object_manager = std::make_unique<ObjectManager>();
    this->animation_manager = std::make_unique<AnimationManager>();
}

void Scene::init(std::shared_ptr<ShaderLoader> preloaded_shader_loader) {
    this->shader_loader = std::move(preloaded_shader_loader);

    // create bezier
    // note: this is just a test, this should be done in a better way
    // and importantly, in a better place
    const auto* bezier_model = ModelLoader::getInstance().loadModel("sphere");
    auto bezier_obj = this->draftObject(bezier_model, glm::vec3(-4, 1, 0), "blinn");
    bezier_obj->setProperties(glm::vec3(0.06, 0.75, 0.1),
                              glm::vec3(0.65, 0.84, 0.87),
                              18.5f);
    std::shared_ptr<CubicChain> bezier_animation = std::make_shared<CubicChain>(std::move(bezier_obj), .001f, AnimationArgs::RESTART);
    animation_manager->addAnimation(bezier_animation);
    bezier = bezier_animation.get();
    // ok, awkward part ends here, back to normal

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

    // subscribe single shader to drawable objects inside animations
    for (const auto animation: *animation_manager) {
        animation_manager->applyAnimations([this](Animation* animation) {
            Shader* sh = this->shader_loader->loadShader(animation->getShaderAlias());
            animation->attachShader(sh);
            animation->notifyShader();
        });
    }

    // subscribe single shader to skybox
    if (object_manager->hasSkybox()) {
        auto& skybox = object_manager->getSkybox();
        assignShaderAlias(skybox);
        Shader* sh = this->shader_loader->loadShader(skybox.getShaderAlias());
        skybox.attach(sh);
        skybox.notifyModel();
        skybox.notifyMaterial();
    }

    // create flashlight
    std::unique_ptr<Spotlight> flashlight = std::make_unique<Spotlight>(FLASHLIGHT);
    auto fl_id = light_manager.addLight(std::move(flashlight));
    auto fl = light_manager.getLight(fl_id);
    this->camera->setFlashlight(std::static_pointer_cast<Spotlight>(fl));

    // pass camera and light uniforms to shaders
    camera->start();
    light_manager.notifyShaders();
}

void Scene::prepareObjects() {
    object_manager->preprocess(this->shader_loader.get());
}

std::unique_ptr<DrawableObject> Scene::draftObject(
        const Model* model_ptr,
        const glm::vec3 &position,
        const std::string &shader_name) {
    std::unique_ptr<DrawableObject> object = std::make_unique<DrawableObject>(position, model_ptr,
                                                                              shader_name, scene_ambient);
    return object;
}

std::unique_ptr<DrawableObject>Scene::draftObject(
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

DrawableObject& Scene::appendObject(std::unique_ptr<DrawableObject> object_ptr) {
    auto& obj = object_manager->addObject(std::move(object_ptr));
    obj.setAmbient(scene_ambient);
    return obj;
}

DrawableObject& Scene::assignSkybox(const Model* model_ptr) {
    std::unique_ptr<DrawableObject> object = std::make_unique<DrawableObject>(glm::vec3(0, 0, 0), model_ptr,
                                                                              "skybox", scene_ambient);
    auto& obj = object_manager->assignSkybox(std::move(object));
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
    last_frame_time = (float)glfwGetTime() * FRAME_TIME_MULTIPLIER;
    while (!is_finished) {
        this->prepareObjects();

        auto current_frame_time = (float)glfwGetTime() * FRAME_TIME_MULTIPLIER;
        float delta_time = current_frame_time - last_frame_time;
        last_frame_time = current_frame_time;

        continuousMovement(delta_time);
        camera->jumpProgress(delta_time);

        // wipe the stencil buffer identifying objects
        glStencilFunc(GL_ALWAYS, 0, 0xFF);
        // wipe the drawing surface clear
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if (const auto& skybox = object_manager->getSkybox(); object_manager->hasSkybox()) {
            if (CYCLE_CULL_FACE_SKYBOX)
                glDisable(GL_CULL_FACE);
            glDisable(GL_DEPTH_TEST);
            Shader* sh = shader_loader->loadShader(skybox.getShaderAlias());
            skybox.notifyModelParameters();
            sh->lazyPassUniforms();
            skybox.draw();
            glEnable(GL_DEPTH_TEST);
            if (CYCLE_CULL_FACE_SKYBOX)
                glEnable(GL_CULL_FACE);
        }

        for (const auto object: *object_manager) {
            Shader* sh = shader_loader->loadShader(object->getShaderAlias());
            object->notifyModelParameters();
            sh->lazyPassUniforms();
            object->draw();
        }

        // animations
        for (const auto animation: *animation_manager) {
            animation_manager->applyAnimations([this, &delta_time](Animation* animation) {
                const SHADER_ALIAS_DATATYPE current_alias = animation->getShaderAlias();
                Shader* sh = shader_loader->loadShader(current_alias);
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
        case GLFW_KEY_I:
            showBuffers(last_mouse_x, last_mouse_y);
            break;
        case GLFW_KEY_B:
            printf("Bezier mode\n");
            mode = 'b';
            break;
        case GLFW_KEY_N:
            printf("Tree mode\n");
            mode = 't';
            break;
        case GLFW_KEY_O:
            deleteTargetObject();
            break;
        default:
            break;
    }
}

void Scene::handleKeyEventRelease(int key, int scancode, int action, int mods) { }

Scene::~Scene() {}

void Scene::handleMouseMovementEvent(double x_pos, double y_pos) {
    last_mouse_x = x_pos;
    last_mouse_y = y_pos;

    if (!right_mouse_button_pressed)
        return;

    double mouse_x = camera->getMouseX();
    double mouse_y = camera->getMouseY();
    double x_offset = x_pos - mouse_x;
    double y_offset = mouse_y - y_pos;
    camera->setMouseXY(x_pos, y_pos);

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
        case GLFW_MOUSE_BUTTON_LEFT:
            if (mode == 't')
                handlePlantTree(last_mouse_x, last_mouse_y);
            else if (mode == 'b')
                handleBezier(last_mouse_x, last_mouse_y);
        default:
            break;
    }
}

void Scene::showBuffers(double x_pos, double y_pos) {
    glm::vec4 color = camera->getColorBuffer(x_pos, y_pos);
    float depth = camera->getDepthBuffer(x_pos, y_pos);
    char index = camera->getStencilBuffer(x_pos, y_pos);
    glm::vec3 pos = camera->getWorldPosition(x_pos, y_pos, depth);

    printf("Clicked on pixel %f, %f, color (%.0f,%.0f,%.0f,%.0f), depth %f, stencil index %u\n",
           x_pos, y_pos, color[0], color[1], color[2], color[3], depth, index);
    printf("World coordinates: %f, %f, %f\n", pos.x, pos.y, pos.z);
}

void Scene::handleBezier(double x_pos, double y_pos) {
    if (bezier == nullptr)
        return;

    float depth = camera->getDepthBuffer(x_pos, y_pos);
    glm::vec3 pos = camera->getWorldPosition(x_pos, y_pos, depth);

    incomplete_bezier_points.push_back(pos);

    if (incomplete_bezier_points.size() == 3) {
        glm::mat3x3 points = glm::mat3x3(
                incomplete_bezier_points[0],
                incomplete_bezier_points[1],
                incomplete_bezier_points[2]
        );
        bezier->addControlPoint(points);
        incomplete_bezier_points.clear();
        printf("Next bezier points added\n");
    } else {
        printf("%zu/3 bezier points added\n", incomplete_bezier_points.size());
    }
}

void Scene::handlePlantTree(double x_pos, double y_pos) {
    float depth = camera->getDepthBuffer(x_pos, y_pos);
    glm::vec3 pos = camera->getWorldPosition(x_pos, y_pos, depth);

    plantTree(pos.x, 0, pos.z);
    printf("Tree planted at %f, %f, %f\n", pos.x, 0., pos.z);
}

void Scene::plantTree(float x, float y, float z) {
    const auto* tree_model = ModelLoader::getInstance().loadModel("tree");
    auto tree_obj = this->draftObject(tree_model, glm::vec3(x, y, z), "blinn");
    tree_obj->setProperties(glm::vec3(0.55, 0.75, 0.1),
                           glm::vec3(0.99, 0.15, 0.1),
                           2.5f);

    // we need to mark the object as interact before we pass it to the object manager
    // to avoid race condition where the interact flag is set after the object's enqueue
    tree_obj->markInteract();
    this->appendObject(std::move(tree_obj));
}

void Scene::deleteTargetObject() {
    char id = camera->getStencilBuffer(last_mouse_x, last_mouse_y);
    if (id != 0) {
        object_manager->deleteByInteractID(id);
        printf("Object with id %d deleted\n", id);
    } else {
        printf("No object to delete\n");
    }
}
