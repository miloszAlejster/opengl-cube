#shader vertex
#version 330 core

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 scale;
layout(location = 0) in vec3 aPos;

void main() {
    gl_Position = projection * view * model * scale * vec4(aPos, 1.0f);
};

#shader fragment
#version 330 core

out vec4 FragColor;

void main() {
    FragColor = vec4(1.0f);
};