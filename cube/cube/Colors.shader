#shader vertex
#version 330 core

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 vertexColor;

void main(){
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    vertexColor = aColor;
};

#shader fragment
#version 330 core

out vec4 FragColor;
in vec3 vertexColor;

void main(){
    FragColor = vec4(vertexColor, 1.0f);
};