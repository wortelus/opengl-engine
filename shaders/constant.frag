#version 330

struct Material {
    vec3 ambient;
};

uniform Material material;

out vec4 out_color;

void main () {
    out_color = vec4(material.ambient, 1.0);
}