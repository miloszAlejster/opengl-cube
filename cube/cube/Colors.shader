#shader vertex
#version 330 core

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;
out vec3 vertexColor;
out vec3 Normal;
out vec3 FragPos;

void main(){
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    FragPos = vec3(model * vec4(aPos, 1.0f));
    vertexColor = aColor;
    Normal = aNormal;
};

#shader fragment
#version 330 core

uniform vec3 lightPos;
uniform vec3 lightColor;
out vec4 FragColor;
in vec3 vertexColor;
in vec3 Normal;
in vec3 FragPos;

void main(){
    // ambient
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * vec3(1.f, 1.f, 1.f);

    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * vec3(1.f, 1.f, 1.f);

    vec3 result = (ambient + diffuse) * vertexColor;
    FragColor = vec4(result, 1.0f);
};