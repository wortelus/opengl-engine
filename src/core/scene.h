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
#include "../shaders/shader_loader.h"
#include "../models/drawable.h"
#include "../rendering/camera.h"
#include "../rendering/light/light.h"
#include "../rendering/light_manager.h"
#include "../rendering/object_manager.h"
#include "../rendering/animation_manager.h"
#include "../models/animations/cubic_chain.h"

class Scene {
private:
    char scene_id;
    GLFWwindow* window;
    std::shared_ptr<ShaderLoader> shader_loader;
    std::unique_ptr<ObjectManager> object_manager;
    std::unique_ptr<AnimationManager> animation_manager;
    LightManager light_manager;

    glm::vec3 scene_ambient = AMBIENT_LIGHT;

    std::unique_ptr<Camera> camera;
    const glm::vec3 scene_up = glm::vec3(0.0f, 1.0f, 0.0f);

    bool right_mouse_button_pressed = false;
    double last_mouse_x = 0;
    double last_mouse_y = 0;
    float last_frame_time = 0.0f;

    char mode = 't'; // t - tree planting, b - bezier adding
    std::vector<glm::vec3> incomplete_bezier_points;
    CubicChain* bezier;

    bool is_finished = false;
private:
    void plantTree(float x, float y, float z);
    void showBuffers(double x_pos, double y_pos);
    void deleteTargetObject();
public:
    void setAmbient(const glm::vec3& ambient) { scene_ambient = ambient; }
    void assignShaderAlias(DrawableObject& object);

    std::unique_ptr<DrawableObject> draftObject(const Model* model_ptr,
                                                const glm::vec3& position,
                                                const std::string& shader_name);
    std::unique_ptr<DrawableObject> draftObject(const Model* model_ptr,
                                                const glm::vec3& position,
                                                const std::string& shader_name,
                                                const glm::vec3& axis);
    DrawableObject& appendObject(const Model* model_ptr,
                                 const glm::vec3& position,
                                 const std::string& shader_name);
    DrawableObject& appendObject(std::unique_ptr<DrawableObject> object_ptr);
    void appendAnimation(const std::shared_ptr<Animation>& animation);
    void appendLight(const Light& light);
    void appendLight(const std::shared_ptr<Light>& light);

    DrawableObject& assignSkybox(const Model* model_ptr);
public:
    Scene(const char& id, GLFWwindow& window_reference, const int& initial_width, const int& initial_height);
    ~Scene();

    void init(std::shared_ptr<ShaderLoader> preloaded_shader_loader);
    void prepareObjects();
    void run();

    [[nodiscard]] char getSceneId() const { return scene_id; }
    [[nodiscard]] bool isFinished() const { return is_finished; }
    void finish() { is_finished = true; }

    inline void continuousMovement(const float& delta_time);
    void update_aspect_ratio(const int& new_width, const int& new_height);

    void handleBezier(double x_pos, double y_pos);
    void handlePlantTree(double x_pos, double y_pos);

    void handleKeyEventPress(int key, int scancode, int action, int mods);
    void handleKeyEventRelease(int key, int scancode, int action, int mods);
    void handleMouseButtonEventPress(int button, int action, int mods);
    void handleMouseButtonEventRelease(int button, int action, int mods);
    void handleMouseMovementEvent(double x_pos, double y_pos);
};


#endif //ZPG_SCENE_H
