#version 330

in vec4 ex_world_position;
in vec3 ex_world_normal;
in vec3 ex_view_direction;

const int MAX_LIGHTS = 10;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct PointLight {
    vec3 position;
    vec3 color;
    float intensity;
    float constant;
    float linear;
    float quadratic;
};

uniform Material material;
uniform PointLight lights[MAX_LIGHTS];
uniform int num_lights;

out vec4 out_color;

vec3 calcPointLight(PointLight light, vec3 normal, vec3 frag_pos_world, vec3 view_direction_norm) {
    vec3 light_direction_n = normalize(light.position - frag_pos_world);
    float reflection_n = dot(light_direction_n, normal);
    float diff = max(reflection_n, 0.0);

    float dist = length(light.position - frag_pos_world);
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * dist * dist);

    // TODO: maybe optimize vector multiplication
    vec3 diffuse  =     material.diffuse  * diff * light.intensity * light.color * attenuation;

    // calculate specular even if the light is behind the surface
    vec3 reflect_direction = reflect(-light_direction_n, normal);
    float spec = pow(max(dot(view_direction_norm, reflect_direction), 0.0), material.shininess);
    vec3 specular =     material.specular * spec * light.intensity * light.color * attenuation;
    return (diffuse + specular);
}

void main(void) {
    vec3 view_direction_norm = normalize(ex_view_direction);
    vec3 world_normal_norm = normalize(ex_world_normal);

    vec3 color_sum = vec3(0.0);
    for(int i = 0; i < num_lights; ++i) {
        color_sum += calcPointLight(lights[i], world_normal_norm, ex_world_position.xyz, view_direction_norm);
    }

    out_color = vec4(material.ambient + color_sum, 1.0);
}