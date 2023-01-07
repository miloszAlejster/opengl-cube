#shader vertex
#version 330 core

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
layout(location = 0) in vec3 aPos;
layout(location = 2) in vec3 aNormal;
out vec3 Normal;
out vec3 FragPos;

void main(){
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    FragPos = vec3(model * vec4(aPos, 1.0f));
    Normal = aNormal;
};

#shader fragment
#version 330 core

in vec3 Normal;
in vec3 FragPos;
uniform vec3 cubeColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
out vec4 FragColor;

void main(){
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * cubeColor;
    FragColor = vec4(result, 1.0f);
};