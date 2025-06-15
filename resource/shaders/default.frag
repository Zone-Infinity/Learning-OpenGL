#version 410 core
out vec4 FragColor;

in vec3 color;
in vec2 texCoord;
in vec3 normal;
in vec3 currentPos;

uniform sampler2D tex0;
uniform sampler2D tex1;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main() {
    float ambient = 0.20f;

    vec3 lightDir = normalize(lightPos - currentPos);
    float diffused = max(dot(normalize(normal), lightDir), 0.0f);

    float specularStrength = 0.50f;
    vec3 viewDir = normalize(camPos - currentPos);
    vec3 reflectionDir = reflect(-lightDir, normal);
    float specAmount = pow(max(dot(viewDir, reflectionDir), 0.0f), 16);
    float specular = specularStrength * specAmount;

    FragColor = texture(tex0, texCoord) * lightColor * (diffused + ambient + texture(tex1, texCoord).r* specular);
}