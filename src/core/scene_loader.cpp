// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  22/10/2023

#include "scene_loader.h"
#include "../../assets/bushes.h"
#include "../../assets/sphere.h"
#include "../../assets/tree.h"
#include "../../assets/suzi_flat.h"
#include "../../assets/suzi_smooth.h"
#include "../../assets/gift.h"
#include "../../assets/plain.h"
#include "../models/animations/centric_model.h"

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
        case 3:
            return loadSceneD(window_reference, initial_width, initial_height);
        case 4:
            return loadSceneE(window_reference, initial_width, initial_height);
        case 5:
            return loadSceneF(window_reference, initial_width, initial_height);
        case 6:
            return loadSceneG(window_reference, initial_width, initial_height);
        default:
            *scene_id = 0;
            return loadSceneA(window_reference, initial_width, initial_height);
    }
}

std::unique_ptr<Scene>
SceneLoader::loadSceneA(GLFWwindow& window_reference, const int& initial_width, const int& initial_height) {
    const float height = -4.5;

    std::unique_ptr<Scene> scene = std::make_unique<Scene>(0, window_reference, initial_width, initial_height);
    auto& sphere_south_object = scene->appendObject(sphere, sizeof(sphere),
                                                    glm::vec3(0.f, height, -2.f), "phong");
    sphere_south_object.setProperties(glm::vec3(0.385, 0.647, 0.812),
                                      glm::vec3(1.0, 1.0, 1.0),
                                      32.f);

    auto& sphere_east_object = scene->appendObject(sphere, sizeof(sphere),
                                                   glm::vec3(-2.f, height, 0.f), "phong");
    sphere_east_object.setProperties(glm::vec3(0.385, 0.647, 0.812),
                                     glm::vec3(1.0, 1.0, 1.0),
                                     32.f);

    auto& sphere_north_object = scene->appendObject(sphere, sizeof(sphere),
                                                    glm::vec3(0.f, height, 2.f), "phong");
    sphere_north_object.setProperties(glm::vec3(0.385, 0.647, 0.812),
                                      glm::vec3(1.0, 1.0, 1.0),
                                      32.f);

    auto& sphere_west_object = scene->appendObject(sphere, sizeof(sphere),
                                                   glm::vec3(2.f, height, 0.f), "phong");
    sphere_west_object.setProperties(glm::vec3(0.385, 0.647, 0.812),
                                      glm::vec3(1.0, 1.0, 1.0),
                                      32.f);

    std::shared_ptr<Light> light_a = std::make_unique<Light>(glm::vec3(0.f, height, 0.f),
                                                             glm::vec3(1.f, 1.f, 1.f),
                                                             1.f,
                                                             1.f, 0.1f, 0.01f);
    scene->appendLight(light_a);
    return std::move(scene);
}

std::unique_ptr<Scene>
SceneLoader::loadSceneB(GLFWwindow& window_reference, const int& initial_width, const int& initial_height) {
    std::unique_ptr<Scene> scene = std::make_unique<Scene>(1, window_reference, initial_width, initial_height);
    auto& sphere_south_object = scene->appendObject(sphere, sizeof(sphere),
                                                    glm::vec3(0.f, 0.f, -2.f), "phong");
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
    auto& sphere_obj = scene->appendObject(sphere, sizeof(sphere),
                                           glm::vec3(-1.f, 1.f, -1.f), "phong");
    sphere_obj.setProperties(glm::vec3(0.6, 0.45, 0.0),
                             glm::vec3(0.6, 0.25, 1.0),
                             12.f);

    auto& tree_obj = scene->appendObject(tree, sizeof(tree),
                                         glm::vec3(2.f, 0.f, 0.f), "blinn");
    tree_obj.setProperties(glm::vec3(0.45, 0.75, 0.1),
                           glm::vec3(0.99, 0.15, 0.1),
                           5.f);


    auto& suzi_smooth_obj_a = scene->appendObject(suziSmooth, sizeof(suziSmooth),
                                                  glm::vec3(-4.f, 2.f, -8.f), "phong");
    suzi_smooth_obj_a.setProperties(glm::vec3(0.70, 0.15, 0.65),
                                    glm::vec3(1.0, 0.9, 0.1),
                                    12.f);


    auto& suzi_smooth_obj_b = scene->appendObject(suziSmooth, sizeof(suziSmooth),
                                                  glm::vec3(-2.f, 2.f, -8.f), "blinn");
    suzi_smooth_obj_b.setProperties(glm::vec3(0.1, 0.2, 0.85),
                                    glm::vec3(0.3, 0.95, 0.40),
                                    12.f);


    auto& plain_obj = scene->appendObject(plain, sizeof(plain),
                                          glm::vec3(0.f, 0.f, 0.f), "lambert");
    plain_obj.setProperties(glm::vec3(0.05, 0.1, 0.01),
                            glm::vec3(0.15, 0.75, 0.45),
                            glm::vec3(0.0, 0.0, 0.0),
                            0.f);
    plain_obj.scale(glm::vec3(128.f, 1.f, 128.f));


    glm::vec3 sun_position = glm::vec3(-4.f, 8.f, -4.f);
    float sun_radius = 2.0f;

    auto& sun_obj = scene->appendObject(sphere, sizeof(sphere),
                                        sun_position, "blinn");
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

std::unique_ptr<Scene>
SceneLoader::loadSceneD(GLFWwindow &window_reference, const int &initial_width, const int &initial_height) {
    float height = -2.0f;
    glm::vec3 axis = glm::vec3(0.0f, 1.0f, 1.0f);

    std::unique_ptr<Scene> scene = std::make_unique<Scene>(2, window_reference, initial_width, initial_height);
    scene->setAmbient(glm::vec3(0.5, 0.5, 0.5));


    // sun
    auto sun_obj = scene->newObject(sphere, sizeof(sphere),
                                        glm::vec3(0, height, 0), "blinn");
    sun_obj->setAmbient(glm::vec3(1.0, 0.75, 0.0));
    sun_obj->setProperties(glm::vec3(1.0, 0.15, 0.0),
                          glm::vec3(1.0, 0.0, 0.0),
                          12.f);

    std::shared_ptr<CentricComposite> sun_composite = std::make_shared<CentricComposite>(sun_obj);

    // earth
    auto earth_obj = scene->newObject(sphere, sizeof(sphere),
                                        glm::vec3(4, height, 0), "blinn", axis);
    earth_obj->setAmbient(glm::vec3(0.0, 0.75, 1.0));
    earth_obj->setProperties(glm::vec3(0.0, 0.15, 1.0),
                             glm::vec3(1.0, 1.0, 1.0),
                          12.f);

    std::shared_ptr<CentricComposite> earth_composite = std::make_shared<CentricComposite>(earth_obj);
    earth_composite->setMultiplier(1.f);

    // moon
    auto moon_obj = scene->newObject(sphere, sizeof(sphere),
                                        glm::vec3(6, height, 0), "blinn", axis);
    moon_obj->setAmbient(glm::vec3(0.5, 0.5, 0.5));
    moon_obj->setProperties(glm::vec3(0.5, 0.5, 0.5),
                          glm::vec3(0.5, 0.5, 0.5),
                          12.f);
    moon_obj->scale(glm::vec3(-0.75f, -0.75f, -0.75f));

    std::shared_ptr<CentricModelLeaf> moon_leaf = std::make_shared<CentricModelLeaf>(moon_obj);
    moon_leaf->setMultiplier(1.f);


    // mars
    auto mars_obj = scene->newObject(sphere, sizeof(sphere),
                                     glm::vec3(8, height, 0), "blinn", axis);
    mars_obj->setAmbient(glm::vec3(0.7, 0.2, 0.0));
    mars_obj->setProperties(glm::vec3(0.8, 0.3, 0.0),
                            glm::vec3(1.0, 1.0, 1.0),
                            50.f);


    std::shared_ptr<CentricModelLeaf> mars_leaf = std::make_shared<CentricModelLeaf>(mars_obj);
    mars_leaf->setMultiplier(0.8f);

    // jupiter
    auto jupiter_obj = scene->newObject(sphere, sizeof(sphere),
                                        glm::vec3(14, height, 0), "blinn", axis);
    jupiter_obj->setAmbient(glm::vec3(0.9, 0.7, 0.5));
    jupiter_obj->setProperties(glm::vec3(1.0, 0.8, 0.6),
                               glm::vec3(1.0, 1.0, 1.0),
                               40.f);

    std::shared_ptr<CentricModelLeaf> jupiter_leaf = std::make_shared<CentricModelLeaf>(jupiter_obj);
    jupiter_leaf->setMultiplier(0.6f);

    // saturn
    auto saturn_obj = scene->newObject(sphere, sizeof(sphere),
                                       glm::vec3(20, height, 0), "blinn", axis);
    saturn_obj->setAmbient(glm::vec3(0.8, 0.6, 0.2));
    saturn_obj->setProperties(glm::vec3(0.9, 0.7, 0.3),
                              glm::vec3(1.0, 1.0, 1.0),
                              45.f);

    std::shared_ptr<CentricModelLeaf> saturn_leaf = std::make_shared<CentricModelLeaf>(saturn_obj);
    saturn_leaf->setMultiplier(0.4f);

    // uranus
    auto uranus_obj = scene->newObject(sphere, sizeof(sphere),
                                       glm::vec3(26, height, 0), "blinn", axis);
    uranus_obj->setAmbient(glm::vec3(0.4, 0.7, 0.7));
    uranus_obj->setProperties(glm::vec3(0.5, 0.8, 0.8),
                              glm::vec3(1.0, 1.0, 1.0),
                              50.f);

    std::shared_ptr<CentricModelLeaf> uranus_leaf = std::make_shared<CentricModelLeaf>(uranus_obj);
    uranus_leaf->setMultiplier(0.3f);

    // neptune
    auto neptune_obj = scene->newObject(sphere, sizeof(sphere),
                                        glm::vec3(32, height, 0), "blinn", axis);
    neptune_obj->setAmbient(glm::vec3(0.04, 0.18, 0.55));
    neptune_obj->setProperties(glm::vec3(0.05, 0.2, 0.6),
                               glm::vec3(1.0, 1.0, 1.0),
                               50.f);

    std::shared_ptr<CentricModelLeaf> neptune_leaf = std::make_shared<CentricModelLeaf>(neptune_obj);
    neptune_leaf->setMultiplier(0.2f);


    sun_composite->addModel(earth_composite);
    sun_composite->addModel(mars_leaf);
    earth_composite->addModel(moon_leaf);
    sun_composite->addModel(jupiter_leaf);
    sun_composite->addModel(saturn_leaf);
    sun_composite->addModel(uranus_leaf);
    sun_composite->addModel(neptune_leaf);


    std::shared_ptr<Light> light_a = std::make_unique<Light>(glm::vec3(0.f, height, 0),
                                                             glm::vec3(1.f, 1.f, 1.f),
                                                             1.f,
                                                             1.f, 0.1f, 0.01f); // almost no drop-off

    scene->appendLight(light_a);

    // building
    scene->appendAnimation(sun_composite);
    return std::move(scene);
}

std::unique_ptr<Scene>
SceneLoader::loadSceneE(GLFWwindow &window_reference, const int &initial_width, const int &initial_height) {
    std::unique_ptr<Scene> scene = std::make_unique<Scene>(2, window_reference, initial_width, initial_height);
    scene->setAmbient(glm::vec3(0.1, 0.1, 0.1));

    auto& tree_first = scene->appendObject(tree, sizeof(tree),
                       glm::vec3(-2, 0, -2), "blinn");
    tree_first.setProperties(glm::vec3(0.35, 0.65, 0.05),
                           glm::vec3(0.8, 0.15, 0.1),
                           5.f);

    std::shared_ptr<Light> light_first = std::make_unique<Light>(glm::vec3(0.f, 5.f, 0.f),
                                                             glm::vec3(1.f, 1.0f, 0.8f),
                                                             0.25f,
                                                             1.f, 0.1f, 0.01f);
    scene->appendLight(light_first);

    float tree_height = 0.0f;
    float light_height = 5.0f;

    float tree_radius = 2.0f;

    float range = 100.f;

    for (int i = 0; i < 150; i++) {
        float rand_x = ((float)rand() / RAND_MAX) * range - range / 2.0f;
        float rand_z = ((float)rand() / RAND_MAX) * range - range / 2.0f;

        auto& tree_obj = scene->appendObject(tree, sizeof(tree),
                                             glm::vec3(rand_x, tree_height, rand_z), "blinn");
        tree_obj.setProperties(glm::vec3(0.55, 0.75, 0.1),
                               glm::vec3(0.99, 0.15, 0.1),
                               2.5f);
    }

    for (int i = 0; i < 25; i++) {
        float rand_x = ((float)rand() / RAND_MAX) * range - range / 2.0f;
        float rand_z = ((float)rand() / RAND_MAX) * range - range / 2.0f;

        int rand_obj = ((float)rand() / RAND_MAX) * 4.0f;

        float rand_rotate = ((float)rand() / RAND_MAX) * 360.0f;
        float rand_scale = ((float)rand() / RAND_MAX) * 2.f + 2.f;

        switch(rand_obj) {
            case 0: {
                auto& bushes_obj = scene->appendObject(bushes, sizeof(bushes),
                                                              glm::vec3(rand_x, tree_height, rand_z), "blinn");
                bushes_obj.setProperties(glm::vec3(0.55, 0.95, 0.1),
                                         glm::vec3(0.99, 0.15, 0.1),
                                         32.f);
                bushes_obj.scale(glm::vec3(rand_scale, rand_scale, rand_scale));
                bushes_obj.rotate(glm::vec3(0.f, rand_rotate, 0.f));
                break;
            }
            case 1: {
                auto& gift_obj = scene->appendObject(gift, sizeof(gift),
                                                              glm::vec3(rand_x, tree_height, rand_z), "phong");
                gift_obj.setProperties(glm::vec3(0.9, 0.05, 0.1),
                                       glm::vec3(0.75, 0.15, 0.1),
                                         glm::vec3(0.75, 0.85, 0.8),
                                         65.f);
                gift_obj.scale(glm::vec3(2., 2., 2.));
                gift_obj.rotate(glm::vec3(0.f, rand_rotate, 0.f));
                break;
            }
            case 2: {
                auto& sphere_obj = scene->appendObject(sphere, sizeof(sphere),
                                                              glm::vec3(rand_x, tree_height + 1, rand_z), "blinn");
                sphere_obj.setProperties(glm::vec3(0.9, 0.02, 0.95),
                                         glm::vec3(0.99, 0.66, 0.96),
                                         65.f);
                break;
            }
            case 3: {
                auto& suzi_smooth_obj_a = scene->appendObject(suziSmooth, sizeof(suziSmooth),
                                                              glm::vec3(rand_x, tree_height + 1, rand_z), "phong");
                suzi_smooth_obj_a.setProperties(glm::vec3(0.55, 0.05, 0.85),
                                                glm::vec3(0.99, 0.55, 0.85),
                                                32.f);
                suzi_smooth_obj_a.scale(glm::vec3(rand_scale, rand_scale, rand_scale));
                suzi_smooth_obj_a.rotate(glm::vec3(0.f, rand_rotate, 0.f));
            }
        }
    }


    for (int i = 0; i < 8; i++) {
        float rand_x = ((float)rand() / RAND_MAX) * range - range / 2.0f;
        float rand_z = ((float)rand() / RAND_MAX) * range - range / 2.0f;

        std::shared_ptr<Light> light_a = std::make_unique<Light>(glm::vec3(rand_x, light_height, rand_z),
                                                                 glm::vec3(1.f, 1.f, 1.f),
                                                                 5.f,
                                                                 5.f, 0.1f, 0.01f); // almost no drop-off
        scene->appendLight(light_a);
    }

    auto& plain_obj = scene->appendObject(plain, sizeof(plain),
                                          glm::vec3(0.f, 0.f, 0.f), "lambert");
    plain_obj.setProperties(glm::vec3(0.05, 0.1, 0.01),
                            glm::vec3(0.15, 0.45, 0.25),
                            glm::vec3(0.0, 0.0, 0.0),
                            0.f);
    plain_obj.scale(glm::vec3(128.f, 1.f, 128.f));

    return std::move(scene);
}

std::unique_ptr<Scene>
SceneLoader::loadSceneF(GLFWwindow &window_reference, const int &initial_width, const int &initial_height) {
    std::unique_ptr<Scene> scene = std::make_unique<Scene>(1, window_reference, initial_width, initial_height);
    auto& sphere_south_object = scene->appendObject(sphere, sizeof(sphere),
                                                    glm::vec3(0.f, 0.f, -2.f), "phong_creep");
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
SceneLoader::loadSceneG(GLFWwindow &window_reference, const int &initial_width, const int &initial_height) {
    std::unique_ptr<Scene> scene = std::make_unique<Scene>(1, window_reference, initial_width, initial_height);
    auto& sphere_obj = scene->appendObject(sphere, sizeof(sphere),
                                           glm::vec3(0.f, 0.f, -2.f), "blinn");
    sphere_obj.setProperties(glm::vec3(1.0, 1.0, 0.0),
                             glm::vec3(1.0, 1.0, 1.0),
                             1.f);

    auto& suzie_obj = scene->appendObject(suziSmooth, sizeof(suziSmooth),
                                          glm::vec3(0.f, 0.f, 0.f), "blinn");
    suzie_obj.setProperties(glm::vec3(1.0, 1.0, 0.0),
                            glm::vec3(1.0, 1.0, 1.0),
                            1.f);

    auto& plain_obj = scene->appendObject(plain, sizeof(plain),
                                          glm::vec3(0.f, -1.f, 2.f), "blinn");
    plain_obj.setAmbient(glm::vec3(0.05, 0.1, 0.01));
    plain_obj.setDiffuse(glm::vec3(0.15, 0.75, 0.45));
    plain_obj.scale(glm::vec3(128.f, 1.f, 128.f));

    auto& gift_obj = scene->appendObject(gift, sizeof(gift),
                                         glm::vec3(0.f, 0.f, 4.f), "blinn");
    gift_obj.setProperties(glm::vec3(0.8, 0.1, 0.01),
                           glm::vec3(0.15, 0.75, 0.45),
                           glm::vec3(0.7, 0.7, 0.7),
                           32.f);

    auto& tree_obj = scene->appendObject(tree, sizeof(tree),
                                         glm::vec3(0, 0, 6), "blinn");
    tree_obj.setProperties(glm::vec3(0.15, 0.25, 0.05),
                           glm::vec3(0.55, 0.95, 0.1),
                           glm::vec3(0.99, 0.15, 0.1),
                           5.f);

    std::shared_ptr<Light> light_a = std::make_unique<Light>(glm::vec3(0.f, 4.f, 0.f),
                                                             glm::vec3(1.f, 1.f, 1.f),
                                                             0.1f,
                                                             0.1f, 0.1f, 0.01f);

    scene->appendLight(light_a);

    return std::move(scene);
}
