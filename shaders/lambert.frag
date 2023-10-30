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
    vec3 light_direction_n = normalize(light.position - frag_pos_world);
    float diff = dot(light_direction_n, normal);

    if (diff > 0.0) {
        float dist = length(light.position - frag_pos_world);
        float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * dist * dist);

        vec3 diffuse = diff * material.diffuse * light.intensity * light.color * attenuation;

        return (diffuse) * object_color;
    } else {
        return vec3(0.0);
    }
}

void main(void) {
    vec3 world_normal_norm = normalize(ex_world_normal);

    vec3 color_sum = vec3(0.0);
    for(int i = 0; i < num_lights; ++i) {
        color_sum += calcLambertLight(lights[i], world_normal_norm, ex_world_position.xyz);
    }

    out_Color = vec4(material.ambient + color_sum, 1.0);
}