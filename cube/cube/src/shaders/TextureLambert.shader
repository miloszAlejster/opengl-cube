#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec2 aTexCoord;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoord;

void main(){
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	FragPos = vec3(model * vec4(aPos, 1.0f));
	Normal = aNormal;
	TexCoord = aTexCoord;
}

#shader fragment
#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform sampler2D Texture;
out vec4 FragColor;

void main(){
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
	FragColor = texture(Texture, TexCoord) * vec4(diffuse, 1.0);
}