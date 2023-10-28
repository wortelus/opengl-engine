// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  22/10/2023

#include "scene_loader.h"
#include "../../assets/sphere.h"
#include "../../assets/tree.h"
#include "../../assets/suzi_flat.h"
#include "../../assets/suzi_smooth.h"
#include "../../assets/gift.h"
#include "../../assets/plain.h"

std::unique_ptr<Scene> SceneLoader::loadScene(int* scene_id, GLFWwindow& window_reference, const int& initial_width,
                                              const int& initial_height) {
    // here, a thought has passed, if we ever would want to preload all scenes
    switch (*scene_id) {
        case 0:
            return loadSceneA(window_reference, initial_width, initial_height);
        case 1:
            return loadSceneB(window_reference, initial_width, initial_height);
        case 2:
            return loadSceneC(window_reference, initial_width, initial_height);
        default:
            *scene_id = 0;
            return loadSceneA(window_reference, initial_width, initial_height);
    }
}

std::unique_ptr<Scene>
SceneLoader::loadSceneA(GLFWwindow& window_reference, const int& initial_width, const int& initial_height) {
    const float height = -3.5;

    std::unique_ptr<Scene> scene = std::make_unique<Scene>(0, window_reference, initial_width, initial_height);
    auto& sphere_south_object = scene->newObject(sphere, sizeof(sphere),
                                                 glm::vec3(0.f, height, -2.f), "lambert");
    sphere_south_object.setColor(glm::vec3(0.385, 0.647, 0.812));
    sphere_south_object.setProperties(glm::vec3(0.385, 0.647, 0.812),
                                      glm::vec3(1.0, 1.0, 1.0),
                                      0.f);

    auto& sphere_east_object = scene->newObject(sphere, sizeof(sphere),
                                                glm::vec3(-2.f, height, 0.f), "phong");
    sphere_east_object.setColor(glm::vec3(0.385, 0.647, 0.812));
    sphere_east_object.setProperties(glm::vec3(0.385, 0.647, 0.812),
                                     glm::vec3(1.0, 1.0, 1.0),
                                     32.f);

    auto& sphere_north_object = scene->newObject(sphere, sizeof(sphere),
                                                 glm::vec3(0.f, height, 2.f), "blinn");
    sphere_north_object.setColor(glm::vec3(0.385, 0.647, 0.812));
    sphere_north_object.setProperties(glm::vec3(0.385, 0.647, 0.812),
                                      glm::vec3(1.0, 1.0, 1.0),
                                      32.f);

    auto& sphere_west_object = scene->newObject(sphere, sizeof(sphere),
                                                glm::vec3(2.f, height, 0.f), "constant");
    sphere_west_object.setColor(glm::vec3(0.385, 0.647, 0.812));

    std::shared_ptr<Light> light_a = std::make_unique<Light>(glm::vec3(0.f, height + 1, 0.f),
                                                             glm::vec3(1.f, 1.f, 1.f),
                                                             1.f,
                                                             1.f, 0.1f, 0.01f);
    scene->appendLight(light_a);
    return std::move(scene);
}

std::unique_ptr<Scene>
SceneLoader::loadSceneB(GLFWwindow& window_reference, const int& initial_width, const int& initial_height) {
    std::unique_ptr<Scene> scene = std::make_unique<Scene>(1, window_reference, initial_width, initial_height);
    auto& sphere_south_object = scene->newObject(sphere, sizeof(sphere),
                                                 glm::vec3(0.f, 0.f, -2.f), "phong");
    sphere_south_object.setColor(glm::vec3(1.0, 1.0, 0.0));
    sphere_south_object.setProperties(glm::vec3(1.0, 1.0, 0.0),
                                      glm::vec3(1.0, 1.0, 1.0),
                                      1.f);

    std::shared_ptr<Light> light_a = std::make_unique<Light>(glm::vec3(0.f, 0.f, -4.f),
                                                             glm::vec3(1.f, 1.f, 1.f),
                                                             1.f,
                                                             0.1f, 0.f, 0.f); // almost no drop-off

    scene->appendLight(light_a);

    return std::move(scene);
}


std::unique_ptr<Scene>
SceneLoader::loadSceneC(GLFWwindow& window_reference, const int& initial_width, const int& initial_height) {
    std::unique_ptr<Scene> scene = std::make_unique<Scene>(2, window_reference, initial_width, initial_height);
    scene->setAmbient(glm::vec3(0.01, 0.01, 0.01));
    auto& sphere_obj = scene->newObject(sphere, sizeof(sphere),
                                        glm::vec3(-1.f, 1.f, -1.f), "phong");
    sphere_obj.setColor(glm::vec3(1.0, 1.0, 0.0));
    sphere_obj.setProperties(glm::vec3(0.6, 0.45, 0.0),
                             glm::vec3(0.6, 0.25, 1.0),
                             12.f);

    auto& tree_obj = scene->newObject(tree, sizeof(tree),
                                      glm::vec3(2.f, 0.f, 0.f), "blinn");
    tree_obj.setColor(glm::vec3(0.4, 0.5, 0.1));
    tree_obj.setProperties(glm::vec3(0.55, 0.95, 0.1),
                           glm::vec3(0.99, 0.15, 0.1),
                           5.f);


    auto& suzi_smooth_obj_a = scene->newObject(suziSmooth, sizeof(suziSmooth),
                                               glm::vec3(-4.f, 2.f, -8.f), "phong");
    suzi_smooth_obj_a.setColor(glm::vec3(0.90, 0.15, 0.75));
    suzi_smooth_obj_a.setProperties(glm::vec3(1.0, 1.0, 1.0),
                                    glm::vec3(1.0, 0.9, 0.1),
                                    12.f);


    auto& suzi_smooth_obj_b = scene->newObject(suziSmooth, sizeof(suziSmooth),
                                               glm::vec3(-2.f, 2.f, -8.f), "blinn");
    suzi_smooth_obj_b.setColor(glm::vec3(0.1, 0.2, 0.95));
    suzi_smooth_obj_b.setProperties(glm::vec3(0.65, 1.0, 0.85),
                                    glm::vec3(0.3, 0.95, 0.40),
                                    12.f);


    auto& plain_obj = scene->newObject(plain, sizeof(plain),
                                       glm::vec3(0.f, 0.f, 0.f), "lambert");
    plain_obj.setColor(glm::vec3(0.2, 0.3, 0.2));
    plain_obj.setProperties(glm::vec3(0.05, 0.1, 0.01),
                            glm::vec3(0.15, 0.75, 0.45),
                            glm::vec3(0.0, 0.0, 0.0),
                            0.f);
    plain_obj.scale(glm::vec3(128.f, 1.f, 128.f));


    glm::vec3 sun_position = glm::vec3(-4.f, 8.f, -4.f);
    float sun_radius = 2.0f;

    auto& sun_obj = scene->newObject(sphere, sizeof(sphere),
                                     sun_position, "blinn");
    sun_obj.setColor(glm::vec3(1.0, 0.5, 0.1));
    sun_obj.setAmbient(glm::vec3(1.0, 0.75, 0.0));
    sun_obj.setProperties(glm::vec3(1.0, 0.15, 0.0),
                          glm::vec3(1.0, 0.0, 0.0),
                          12.f);

    int num_lights = 6;
    for (int i = 0; i < num_lights; i++) {
        float angle = (float) i / num_lights * 2.0f * glm::pi<float>();

        glm::vec3 sun_pos_new = glm::vec3(0.0);
        sun_pos_new.x = sun_position.x + sun_radius * cos(angle);
        sun_pos_new.y = sun_position.y;
        sun_pos_new.z = sun_position.z + sun_radius * sin(angle);

        std::shared_ptr<Light> light_a = std::make_unique<Light>(sun_pos_new - glm::vec3(0.f, 2.f, 0.f),
                                                                 glm::vec3(1.f, 1.0f, 0.8f),
                                                                 0.25f,
                                                                 1.f, 0.1f, 0.01f);
        scene->appendLight(light_a);
    }

    return std::move(scene);
}