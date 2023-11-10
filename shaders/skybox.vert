#version 450
layout(location = 0) in vec3 vec_position;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

out vec3 ex_world_position;

void main () {
    ex_world_position = vec_position;
    mat4 static_view_matrix = mat4(mat3(view_matrix));
    vec4 pos = (projection_matrix * static_view_matrix) * vec4(vec_position, 1.0);
    gl_Position = pos;
}