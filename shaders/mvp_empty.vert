#version 330
layout(location=0) in vec3 vec_position;
layout(location=1) in vec3 vec_normal;
uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;
out vec4 frag_color;
out vec3 frag_normal;
void main () {
     gl_Position = projection_matrix * view_matrix * model_matrix * vec4(vec_position, 1.0);
     frag_color = vec4 (vec_normal, 1.0);
     frag_normal = vec_normal;
}
