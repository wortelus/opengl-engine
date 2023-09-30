//
// Created by wortelus on 29.9.23.
//

#ifndef ZPG_MODEL_H
#define ZPG_MODEL_H

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

#include <vector>
#include <string>
#include "observer.h"

class Model {
    std::vector<IObserver*> observers;

    GLuint vao = 0;
    GLuint vbo = 0;
    GLsizei vertices_count;

    // shader names that are used for this model
    std::string vertex_shader_name;
    std::string fragment_shader_name;

public:
    Model(std::vector<float> vertices);
    ~Model();

    void draw() const;
};


#endif //ZPG_MODEL_H
