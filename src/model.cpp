//
// Created by wortelus on 29.9.23.
//

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

    this->vertices_count = static_cast<GLsizei>(vertices.size());

    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<GLsizei>(this->vertices_count * sizeof(float)), &vertices[0],
                 GL_STATIC_DRAW);

    glGenVertexArrays(1, &this->vao); //generate the VAO
    glBindVertexArray(this->vao); //bind the VAO
    glEnableVertexAttribArray(0); //enable vertex attributes
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void Model::draw() const {
    glBindVertexArray(this->vao);
    glDrawArrays(GL_TRIANGLES, 0, 3); //TODO: not 3?
}

Model::~Model() {
    glDeleteBuffers(1, &this->vbo);
    glDeleteVertexArrays(1, &this->vao);
}
