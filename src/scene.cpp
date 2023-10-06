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
}

void Scene::CreateObjects() {

}

void Scene::Run() {
    float b[] ={
            -.5f, -.5f, .5f, 1, 1, 1, 0, 1,
            -.5f, .5f, .5f, 1, 1, 0, 0, 1,
            .5f, -.5f, .5f, 1, 0, 0, 1, 1,
            .5f, .5f, .5f, 1, 0, 1, 1, 1,
    };
    Model bm = Model(std::vector<float>(b, b + sizeof(b) / sizeof(float)));
    objects.push_back(std::make_unique<DrawableObject>(glm::vec3(0, 0, 0), std::make_unique<Model>(bm), "default"));

    while (!glfwWindowShouldClose(window)) {
        // clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for(const auto & object : objects){
            DrawableObject* d_obj = object.get();
            shaderLoader.LoadShader(d_obj->GetShaderName());
            shaderLoader.PassTransform(d_obj->GetModelMatrix());
            d_obj->Draw();
        }

//        m1.Draw();
//        shaderLoader.LoadShader("default_blue");
//        m2.Draw();
//        shaderLoader.LoadShader("default_red");
//        m3.TestTransform();
//        m3.Draw();

        // Update other events like input handling
        glfwPollEvents();
        // put the stuff we've been drawing onto the display
        glfwSwapBuffers(window);
    }
}

void Scene::HandleKeyEvent(int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_A && action == GLFW_PRESS) {
        objects[0].get()->Move(glm::vec3(-0.1, 0, 0));
    } else if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        objects[0].get()->Move(glm::vec3(0.1, 0, 0));
    } else if (key == GLFW_KEY_W && action == GLFW_PRESS) {
        objects[0].get()->Move(glm::vec3(0, 0.1, 0));
    } else if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        objects[0].get()->Move(glm::vec3(0, -0.1, 0));
    } else if (key == GLFW_KEY_E && action == GLFW_PRESS) {
        objects[0].get()->Rotate(glm::vec3(0.1, 0, 0));
    } else if (key == GLFW_KEY_F && action == GLFW_PRESS) {
        objects[0].get()->Rotate(glm::vec3(-0.1, 0, 0));
    } else if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        objects[0].get()->Rotate(glm::vec3(0, 0.1f, 0));
    } else if (key == GLFW_KEY_G && action == GLFW_PRESS) {
        objects[0].get()->Rotate(glm::vec3(0, -0.1f, 0));
    } else if (key == GLFW_KEY_T && action == GLFW_PRESS) {
        objects[0].get()->Rotate(glm::vec3(0, 0, 0.1f));
    } else if (key == GLFW_KEY_H && action == GLFW_PRESS) {
        objects[0].get()->Rotate(glm::vec3(0, 0, -0.1f));
    }
}

Scene::~Scene() {
    for(auto & object : objects){
        object.reset();
    }
}
