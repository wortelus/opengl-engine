// Creator: Daniel Slavík
// E-Mail: sla0331@vsb.cz
// Date of Creation:  29/9/2023

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

#include "model.h"
#include <algorithm>

Model::Model(std::vector<float> vertices) : vao(0), vbo(0) {

    this->vertices_count = static_cast<GLsizei>(vertices.size() / 4 / 2);

    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<GLsizei>(this->vertices_count * 8 * sizeof(float)), &vertices[0],
                 GL_STATIC_DRAW);

    glGenVertexArrays(1, &this->vao); //generate the VAO
    glBindVertexArray(this->vao); //bind the VAO
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

    // using the following lines we will tell the GPU how to read the data
    // vertex positions ->
    glEnableVertexAttribArray(0); //enable vertex attributes
    glVertexAttribPointer(0, 4,
                          GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    // vertex colors ->
    glEnableVertexAttribArray(1); //enable vertex attributes
    glVertexAttribPointer(1, 4,
                          GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(4 * sizeof(float)));
}

void Model::Draw() const {
    glBindVertexArray(this->vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, this->vertices_count);
}

Model::~Model() {
    glDeleteBuffers(1, &this->vbo);
    glDeleteVertexArrays(1, &this->vao);
}