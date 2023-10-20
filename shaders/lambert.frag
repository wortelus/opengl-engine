#version 330
in vec4 ex_world_position;

in vec3 ex_world_normal;
out vec4 out_Color;
void main(void) {
    vec3 lightPosition = vec3(0.0, 0.0, 0.0);
    vec3 lightVector = normalize(lightPosition - ex_world_position.xyz);

    float dot_product = max(dot(lightVector, normalize(ex_world_normal)), 0.0);
    vec4 diffuse = dot_product * vec4(0.385, 0.647, 0.812, 1.0);
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
    out_Color = ambient + diffuse;
}