// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  5/10/2023

//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>

//Include GLM
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "scene.h"
#include "../assets/sphere.h"
#include "../assets/suzi_smooth.h"

Scene::Scene(GLFWwindow &window_reference, const int initial_width, const int initial_height) : window(&window_reference), width(initial_width), height(initial_height) {
    this->camera = std::make_unique<Camera>(width / height);
    this->objects = std::vector<std::unique_ptr<DrawableObject>>();
}

void Scene::init() {
    this->shaderLoader = ShaderLoader();
    shaderLoader.loadStaticShaders();
    this->createObjects();
}

void Scene::createObjects() {
//    float a[] ={
//            -.5f, -.5f, .5f, 1, 1, 1, 0, 1,
//            -.5f, .5f, .5f, 1, 1, 0, 0, 1,
//            .5f, -.5f, .5f, 1, 0, 0, 1, 1,
//            .5f, .5f, .5f, 1, 0, 1, 1, 1,
//    };
//    float b[] ={
//            .5f, -.5f, -.5f, 1, 1, 1, 0, 1,
//            .5f, .5f, -.5f, 1, 1, 0, 0, 1,
//            .5f, -.5f, .5f, 1, 0, 0, 1, 1,
//            .5f, .5f, .5f, 1, 0, 1, 1, 1,
//    };
//    std::unique_ptr<Model> bm = std::make_unique<Model>(a, sizeof(a) / sizeof(float), 4, true);
//    objects.push_back(std::make_unique<DrawableObject>(glm::vec3(-1.f, 0, 0), std::move(bm), "default"));
//
//    bm = std::make_unique<Model>(b, sizeof(b) / sizeof(float), 4, true);
//    objects.push_back(std::make_unique<DrawableObject>(glm::vec3(-1.f, 0.f, 0), std::move(bm), "default"));
//
//    bm = std::make_unique<Model>(sphere, sizeof(sphere) / sizeof(float), 3, false);
//    objects.push_back(std::make_unique<DrawableObject>(glm::vec3(0.f, 0.f, 0), std::move(bm), "normale_lite"));

    std::unique_ptr<Model> sphere_model = std::make_unique<Model>(sphere, sizeof(sphere) / sizeof(float), 3, false);
    objects.push_back(std::make_unique<DrawableObject>(glm::vec3(-2.f, 0.f, 0.f), std::move(sphere_model), "normale"));

    std::unique_ptr<Model> suzanne = std::make_unique<Model>(suziSmooth, sizeof(suziSmooth) / sizeof(float), 3, false);
    objects.push_back(std::make_unique<DrawableObject>(glm::vec3(0.f, 0.f, 0.f), std::move(suzanne), "normale"));
}

void Scene::run() {
    while (!glfwWindowShouldClose(window)) {
        // clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for(const auto & object : objects){
            DrawableObject* d_obj = object.get();
            shaderLoader.loadShader(d_obj->getShaderName());
            shaderLoader.passModelMatrix(d_obj->getModelMatrix());
            shaderLoader.passViewMatrix(this->camera->getView());
            shaderLoader.passProjectionMatrix(this->camera->getProjection());
            d_obj->draw();
        }

        // update other events like input handling
        glfwPollEvents();
        // put the stuff we've been drawing onto the display
        glfwSwapBuffers(window);
    }
}

void Scene::handleKeyEvent(int key, int scancode, int action, int mods) {
    //
    // camera movement
    //
    if (key == GLFW_KEY_W && action == GLFW_PRESS) {

    } else if (key == GLFW_KEY_S && action == GLFW_PRESS) {

    } else if (key == GLFW_KEY_A && action == GLFW_PRESS) {

    } else if (key == GLFW_KEY_D && action == GLFW_PRESS) {

    } else if (key == GLFW_KEY_Q && action == GLFW_PRESS) {

    }
    //
    // translations
    //
    else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
        for(const auto & object : objects){
            object->move(glm::vec3(-0.1f, 0, 0));
        }
    } else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
        for(const auto & object : objects){
            object->move(glm::vec3(0.1f, 0, 0));
        }
    } else if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
        for(const auto & object : objects){
            object->move(glm::vec3(0, 0.1f, 0));
        }
    } else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
        for(const auto & object : objects){
            object->move(glm::vec3(0, -0.1f, 0));
        }
    }
    //
    // rotation along x-axis
    //
    else if (key == GLFW_KEY_E && action == GLFW_PRESS) {
        for(const auto & object : objects){
            object->rotate(glm::vec3(10.f, 0, 0));
        }
    } else if (key == GLFW_KEY_F && action == GLFW_PRESS) {
        for(const auto & object : objects){
            object->rotate(glm::vec3(-10.f, 0, 0));
        }
    }
    //
    // rotation along y-axis
    //
    else if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        for(const auto & object : objects){
            object->rotate(glm::vec3(0, 10.f, 0));
        }
    } else if (key == GLFW_KEY_G && action == GLFW_PRESS) {
        for(const auto & object : objects){
            object->rotate(glm::vec3(0, -10.f, 0));
        }
    }
    //
    // rotation along z-axis
    //
    else if (key == GLFW_KEY_T && action == GLFW_PRESS) {
        for(const auto & object : objects){
            object->rotate(glm::vec3(0, 0, 10.f));
        }
    } else if (key == GLFW_KEY_H && action == GLFW_PRESS) {
        for(const auto & object : objects){
            object->rotate(glm::vec3(0, 0, -10.f));
        }
    }
    //
    // scaling
    //
    else if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
        for(const auto & object : objects){
            object->scale(glm::vec3(0.1f, 0.1f, 0.1f));
        }
    } else if (key == GLFW_KEY_X && action == GLFW_PRESS) {
        for(const auto & object : objects){
            object->scale(glm::vec3(-0.1f, -0.1f, -0.1f));
        }
    }
}

Scene::~Scene() {
    for(auto & object : objects){
//        object.reset();
    }
}
