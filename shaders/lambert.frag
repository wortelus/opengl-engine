#version 330
in vec4 ex_world_position;
in vec3 ex_world_normal;
in vec3 ex_view_direction;

out vec4 out_Color;

void main(void) {
    vec3 light_position = vec3(0.0, 0.0, 0.0);
    vec3 light_vector = normalize(light_position - ex_world_position.xyz);

    // since both light_vector and ex_world_normal are normalized, we
    // can use the dot product to calculate the cosine of the angle between them
    float dot_product = max(dot(light_vector, normalize(ex_world_normal)), 0.0);
    vec4 diffuse = dot_product * vec4(0.385, 0.647, 0.812, 1.0);
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
    out_Color = ambient + diffuse;
}