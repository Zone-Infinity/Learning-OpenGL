#version 410 core
out vec4 FragColor;

in vec3 color;
in vec2 texCoord;
in vec3 normal;
in vec3 currentPos;

uniform sampler2D tex0;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main() {
    vec3 lightDir = normalize(lightPos - currentPos);

    float ambient = 0.20f;
    float diffused = max(dot(normalize(normal), lightDir), 0.0f);

    float specularStrength = 0.50f;
    vec3 viewDir = normalize(camPos - currentPos);
    vec3 reflectionDir = reflect(-lightDir, normal);
    float specAmount = pow(max(dot(viewDir, reflectionDir), 0.0f), 8);
    float specular = specularStrength * specAmount;

    FragColor = texture(tex0, texCoord) * lightColor * (diffused + ambient + specular);
}