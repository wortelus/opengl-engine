#version 450

in vec3 ex_world_position;

uniform samplerCube texture_sampler;

out vec4 frag_color;

void main () {
    frag_color = texture(texture_sampler, ex_world_position);
}

