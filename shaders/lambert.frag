#version 330

in vec4 ex_world_position;
in vec3 ex_world_normal;
in vec3 ex_view_direction;

const int MAX_LIGHTS = 10;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    // vec3 specular; // Not used in this shader.
};

struct PointLight {
    vec3 position;
    vec3 color;
    float intensity;
    float constant;
    float linear;
    float quadratic;
};

uniform vec3 object_color;
uniform Material material;
uniform PointLight lights[MAX_LIGHTS];
uniform int num_lights;

out vec4 out_Color;

vec3 calcLambertLight(PointLight light, vec3 normal, vec3 frag_pos_world) {
    vec3 light_vector = normalize(light.position - frag_pos_world);
    float dot_product = max(dot(light_vector, normalize(normal)), 0.0);

    float dist = length(light.position - frag_pos_world);
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * dist * dist);

    vec3 ambient = material.ambient;
    vec3 diffuse = dot_product * material.diffuse * light.intensity * light.color * attenuation;

    return (ambient + diffuse) * object_color;
}

void main(void) {
    vec3 result = vec3(0.0);

    for(int i = 0; i < num_lights; ++i) {
        result += calcLambertLight(lights[i], ex_world_normal, ex_world_position.xyz);
    }

    out_Color = vec4(result, 1.0);
}