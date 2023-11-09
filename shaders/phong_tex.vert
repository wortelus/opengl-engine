#version 330
layout(location=0) in vec3 vec_position;
layout(location=1) in vec3 vec_normal;
layout(location=2) in vec2 vec_texcoord;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;
uniform mat3 normal_matrix; //(M-1)T
uniform vec3 camera_position;

out vec4 ex_world_position;
out vec3 ex_world_normal;
out vec3 ex_view_direction;
out vec2 ex_tex_coord;

void main(void) {
    gl_Position = (projection_matrix * view_matrix * model_matrix) * vec4(vec_position, 1.0f);
    ex_world_position = model_matrix * vec4(vec_position, 1.0f);
    ex_world_normal = normal_matrix * vec_normal;
    ex_view_direction = camera_position - ex_world_position.xyz;
    ex_tex_coord = vec_texcoord;
}