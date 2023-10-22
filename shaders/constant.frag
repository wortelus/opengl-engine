#version 330

struct Material {
    vec3 ambient;
};

uniform vec3 object_color;
uniform Material material;

out vec4 out_color;

void main () {
    out_color = vec4(material.ambient * object_color, 1.0);
}