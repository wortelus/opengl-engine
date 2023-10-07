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

Scene::Scene(GLFWwindow &window_reference) : window(&window_reference) {
    this->objects = std::vector<std::unique_ptr<DrawableObject>>();
}

void Scene::Init() {
    this->shaderLoader = ShaderLoader();
    shaderLoader.LoadStaticShaders();
    this->CreateObjects();
}

void Scene::CreateObjects() {
    float a[] ={
            -.5f, -.5f, .5f, 1, 1, 1, 0, 1,
            -.5f, .5f, .5f, 1, 1, 0, 0, 1,
            .5f, -.5f, .5f, 1, 0, 0, 1, 1,
            .5f, .5f, .5f, 1, 0, 1, 1, 1,
    };
    float b[] ={
            .5f, -.5f, -.5f, 1, 1, 1, 0, 1,
            .5f, .5f, -.5f, 1, 1, 0, 0, 1,
            .5f, -.5f, .5f, 1, 0, 0, 1, 1,
            .5f, .5f, .5f, 1, 0, 1, 1, 1,
    };
    float c[] ={
            .5f, -.5f, -.5f, 1, 1, 1, 0, 1,
            .5f, .5f, -.5f, 1, 1, 0, 0, 1,
            .5f, -.5f, .5f, 1, 0, 0, 1, 1,
            .5f, .5f, .5f, 1, 0, 1, 1, 1,
    };
    std::unique_ptr<Model> bm = std::make_unique<Model>(std::vector<float>(a, a + sizeof(a) / sizeof(float)));
    objects.push_back(std::make_unique<DrawableObject>(glm::vec3(0, 0, 0), std::move(bm), "default"));

    bm = std::make_unique<Model>(std::vector<float>(b, b + sizeof(b) / sizeof(float)));
    objects.push_back(std::make_unique<DrawableObject>(glm::vec3(0.f, 0.f, 0), std::move(bm), "default"));
}

void Scene::Run() {
    while (!glfwWindowShouldClose(window)) {
        // clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for(const auto & object : objects){
            DrawableObject* d_obj = object.get();
            shaderLoader.LoadShader(d_obj->GetShaderName());
            shaderLoader.PassTransform(d_obj->GetModelMatrix());
            d_obj->Draw();
        }

        // Update other events like input handling
        glfwPollEvents();
        // put the stuff we've been drawing onto the display
        glfwSwapBuffers(window);
    }
}

void Scene::HandleKeyEvent(int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        for(const auto & object : objects){
            object->Move(glm::vec3(-0.1f, 0, 0));
        }
    } else if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        for(const auto & object : objects){
            object->Move(glm::vec3(0.1f, 0, 0));
        }
    } else if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        for(const auto & object : objects){
            object->Move(glm::vec3(0, 0.1f, 0));
        }
    } else if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        for(const auto & object : objects){
            object->Move(glm::vec3(0, -0.1f, 0));
        }
    } else if (key == GLFW_KEY_E && action == GLFW_PRESS) {
        for(const auto & object : objects){
            object->Rotate(glm::vec3(10.f, 0, 0));
        }
    } else if (key == GLFW_KEY_F && action == GLFW_PRESS) {
        for(const auto & object : objects){
            object->Rotate(glm::vec3(-10.f, 0, 0));
        }
    } else if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        for(const auto & object : objects){
            object->Rotate(glm::vec3(0, 10.f, 0));
        }
    } else if (key == GLFW_KEY_G && action == GLFW_PRESS) {
        for(const auto & object : objects){
            object->Rotate(glm::vec3(0, -10.f, 0));
        }
    } else if (key == GLFW_KEY_T && action == GLFW_PRESS) {
        for(const auto & object : objects){
            object->Rotate(glm::vec3(0, 0, 10.f));
        }
    } else if (key == GLFW_KEY_H && action == GLFW_PRESS) {
        for(const auto & object : objects){
            object->Rotate(glm::vec3(0, 0, -10.f));
        }
    }
}

Scene::~Scene() {
    for(auto & object : objects){
        object.reset();
    }
}
