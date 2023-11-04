#version 330

in vec4 ex_world_position;
in vec3 ex_world_normal;
in vec3 ex_view_direction;

// see const_light.h for the definitions of these constants
const int P_MAX_LIGHTS = 10;
const int D_MAX_LIGHTS = 5;
const int S_MAX_LIGHTS = 5;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    // vec3 specular; --> Not used in this shader.
    // float shininess; --> Not used in this shader.
};

struct PointLight {
    vec3 position;
    vec3 color;
    float intensity;
    float constant;
    float linear;
    float quadratic;
};

struct DirectionalLight {
    vec3 direction;
    vec3 color;
    float intensity;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    vec3 color;
    float intensity;
    float constant;
    float linear;
    float quadratic;
    float cutoff;
    float outer_cutoff;
};

uniform Material material;

uniform PointLight point_lights[P_MAX_LIGHTS];
uniform int point_lights_count;

uniform DirectionalLight directional_lights[D_MAX_LIGHTS];
uniform int directional_lights_count;

uniform SpotLight spotlights[S_MAX_LIGHTS];
uniform int spotlights_count;

out vec4 out_color;

vec3 calcPointLight(PointLight light, vec3 normal, vec3 frag_pos_world) {
    vec3 light_direction_n = normalize(light.position - frag_pos_world);
    float diff = dot(light_direction_n, normal);

    if (diff > 0.0) {
        float dist = length(light.position - frag_pos_world);
        float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * dist * dist);

        return diff * material.diffuse * light.intensity * light.color * attenuation;
    } else {
        return vec3(0.0);
    }
}

vec3 calcDirectionalLight(DirectionalLight light, vec3 normal) {
    vec3 light_direction_n = normalize(-light.direction);
    float diff = max(dot(normal, light_direction_n), 0.0);
    return diff * material.diffuse * light.intensity * light.color;
}

vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 frag_pos_world) {
    vec3 light_direction_n = normalize(light.position - frag_pos_world);
    vec3 spotlight_direction_n = normalize(-light.direction);
    float theta = dot(light_direction_n, spotlight_direction_n);
    float epsilon = light.cutoff - light.outer_cutoff;
    float intensity = clamp((theta - light.outer_cutoff) / epsilon, 0.0, 1.0);

    if (intensity > 0) {
        float diff = max(dot(normal, light_direction_n), 0.0);
        if (diff > 0.0) {
            float dist = length(light.position - frag_pos_world);
            float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * dist * dist);
            return diff * material.diffuse * light.intensity * light.color * attenuation * intensity;
        }
    }
    return vec3(0.0);
}

void main(void) {
    vec3 world_normal_norm = normalize(ex_world_normal);

    vec3 color_sum = vec3(0.0);
    // Point lights
    for(int i = 0; i < point_lights_count; ++i) {
        color_sum += calcPointLight(point_lights[i], world_normal_norm, ex_world_position.xyz);
    }
    // Directional lights
    for(int i = 0; i < directional_lights_count; ++i) {
        color_sum += calcDirectionalLight(directional_lights[i], world_normal_norm);
    }
    // Spotlights
    for(int i = 0; i < spotlights_count; ++i) {
        color_sum += calcSpotLight(spotlights[i], world_normal_norm, ex_world_position.xyz);
    }

    out_color = vec4(material.ambient + color_sum, 1.0);
}