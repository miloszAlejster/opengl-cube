#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 3) in vec2 aTexCoord;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
out vec2 TexCoord;

void main(){
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    TexCoord = aTexCoord;
}

#shader fragment
#version 330 core

in vec2 TexCoord;
uniform sampler2D Texture;
out vec4 FragColor;

void main(){
    FragColor = texture(Texture, TexCoord);
}