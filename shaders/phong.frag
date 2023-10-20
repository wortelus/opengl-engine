#version 330
in vec4 worldPos;
in vec3 worldNor;
out vec4 fragColor;
void main(void) {
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 0.32);
    vec4 specular = specularStrength * spec * lightColor;;
    vec4 objectColor = vec4(0.385, 0.647, 0.812, 1.0);
    fragColor = (ambient + diffuse + specular) * objectColor;
}