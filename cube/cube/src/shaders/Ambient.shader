#shader vertex
#version 330 core

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
layout(location = 0) in vec3 aPos;

void main(){
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
};

#shader fragment
#version 330 core

uniform vec3 cubeColor;
uniform vec3 lightColor;
out vec4 FragColor;

void main(){
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;

    vec3 result = ambient * cubeColor;
    FragColor = vec4(result, 1.0f);
};