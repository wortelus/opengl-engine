#version 330
layout(location=0) in vec3 vec_position;
layout(location=1) in vec3 vec_normal;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

void main () {
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(vec_position, 1.0);
}
