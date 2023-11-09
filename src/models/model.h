// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  29/9/2023

#ifndef ZPG_MODEL_H
#define ZPG_MODEL_H

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

#include <vector>
#include <string>
#include <array>
#include "../util/observer.h"

enum ModelOptions {
    NONE = 0,
    STRIP = (1u << 0),
    TEXTURED = (1u << 1),
};

class Model {
protected:
    std::vector<IObserver*> observers;

    GLuint vao = 0;
    GLuint vbo = 0;
    GLsizei vertices_count;

    // shader names that are used for this model
    std::string vertex_shader_name;
    std::string fragment_shader_name;

    // gl draw type
    ModelOptions model_options = ModelOptions::NONE;
public:
    Model() = default;
    ~Model();

    explicit Model(const float* vertices, int total_count);
    explicit Model(const float* vertices, int total_count, ModelOptions options);

    [[nodiscard]] bool isTextured () const { return this->model_options & ModelOptions::TEXTURED; }
    [[nodiscard]] bool isStrip () const { return this->model_options & ModelOptions::STRIP; }

    void draw() const;
};


#endif //ZPG_MODEL_H
