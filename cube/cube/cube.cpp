#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "linmath.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>

const float cubeVertices[] = {
    // position         // color          // normals          // textures
    -0.5f, -0.5f, -0.5f, 0.9f, 0.1f, 0.9f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.9f, 0.1f, 0.9f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 0.9f, 0.1f, 0.9f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 0.9f, 0.1f, 0.9f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 0.9f, 0.1f, 0.9f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.9f, 0.1f, 0.9f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f, 0.5f, 0.5f, 0.3f, 0.7f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.5f, 0.3f, 0.7f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.5f, 0.3f, 0.7f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.5f, 0.3f, 0.7f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.5f, 0.3f, 0.7f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.5f, 0.3f, 0.7f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

    -0.5f, 0.5f, 0.5f, 0.2f, 0.4f, 0.7f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.2f, 0.4f, 0.7f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.2f, 0.4f, 0.7f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.2f, 0.4f, 0.7f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.2f, 0.4f, 0.7f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.2f, 0.4f, 0.7f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,

    0.5f, 0.5f, 0.5f, 0.5f, 0.1f, 0.1f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 0.5f, 0.1f, 0.1f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.5f, 0.1f, 0.1f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.5f, 0.1f, 0.1f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.5f, 0.1f, 0.1f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.5f, 0.1f, 0.1f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.5f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.5f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.5f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,

    -0.5f, 0.5f, -0.5f, 0.5f, 0.0f, 9.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 0.5f, 0.0f, 9.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.5f, 0.0f, 9.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.5f, 0.0f, 9.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.5f, 0.0f, 9.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 0.5f, 0.0f, 9.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f
};
const vec3 cubePositions[] = {
    {0.0f, 0.0f, 0.0f},
    {2.0f, 5.0f, -15.0f},
    {-1.5f, -2.2f, -2.5f},
    {-3.8f, -2.0f, -12.3f},
    {2.4f, -0.4f, -3.5f},
    {-1.7f, 3.0f, -7.5f},
    {1.3f, -2.0f, -2.5f},
    {1.5f, 2.0f, -2.5f},
    {1.5f, 0.2f, -1.5f},
    {-1.3f, 1.0f, -1.5f},
    {1.0f, 1.0f, 1.0f},
    {2.0f, 2.0f, -15.0f},
    {.0f, 3.f, .1f},
    {-3.8f, -1.0f, -12.3f},
    {2.6f, -1.4f, -33.5f},
    {-10.7f, 3.0f, -7.5f},
    {120.3f, -2.0f, -2.5f},
    {122.5f, 211.0f, -2.5f},
    {12.5f, 22.2f, -1.5f},
    {-11.3f, 14.0f, -1.5f}
};

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}
void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
GLuint setVertexShader(const char* shader, GLuint shaderReference);
GLuint setFragmentShader(const char* shader, GLuint shaderReference);
GLuint setProgram(GLuint program, GLuint vertex, GLuint fragment);
void setVertices(GLuint &VBO, GLuint &VAO);
void mouse_callback(GLFWwindow* window, double x, double y);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
struct mat4 LookAtRH(vec3 eye, vec3 target, vec3 up);
struct mat4 {
    mat4x4 mat;
};
struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};
struct Shader {
    GLuint Vertex;
    GLuint Fragment;
    GLuint Program;
};
float toRadians(float degree);
static ShaderProgramSource ParseShader(const std::string& path);
void addShader(Shader &shader, std::string path);
void deleteShader(Shader& shader);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
vec3 cameraPos = { 0.0f, 0.0f, 3.0f };
vec3 cameraUp = { 0.0f, 1.0f, 0.0f };
vec3 cameraFront = { 0.0f, 0.0f, -1.0f };
// Time between current frame and last frame
float deltaTime = 0.0f; 
// Time of last frame
float lastFrame = 0.0f; 
bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;
float fov = 45.0f;
float lastX = 800.0f / 2.0f;
float lastY = 600.0f / 2.0f;
vec3 lightCol = { 1.0f, 1.0f, 1.0f };
vec3 cubeCol = { 0.670f, 0.234f, 0.605f };
vec3 lightPos = { 3.0f, 2.0f, -1.0f };
vec3 ambientPos = { 0.0f, 0.0f, -1.0f };
vec3 diffusePos = { 2.0f, 0.0f, -1.0f };
vec3 specularPos = { 4.0f, 0.0f, -1.0f };
vec3 phongPos = { 6.0f, 0.0f, -1.0f };
vec3 texturePos = { 8.0f, 0.0f, -1.0f };
vec3 textureLambertPos = { 10.0f, 0.0f, -1.0f };
int txWidth, txHeight, nrChannels;
unsigned char* data = stbi_load("fabric.png", &txWidth, &txHeight, &nrChannels, 0);
bool isObservator = false;
int main(void) {
    GLFWwindow* window;
    GLuint VBO, VAO;
    // init glfw
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // create window
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Cube", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    // callbacks
    glfwSetErrorCallback(error_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    // config
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    gladLoadGL();
    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);
    // texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, txWidth, txHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    // Colors
    Shader ColorShader;
    addShader(ColorShader, "Colors.shader");
    // set uniforms
    GLint m_location = glGetUniformLocation(ColorShader.Program, "model");
    GLint v_location = glGetUniformLocation(ColorShader.Program, "view");
    GLint p_location = glGetUniformLocation(ColorShader.Program, "projection");
    // Light
    Shader LightShader;
    addShader(LightShader, "Light.shader");
    // set uniforms
    GLint mL_location = glGetUniformLocation(LightShader.Program, "model");
    GLint vL_location = glGetUniformLocation(LightShader.Program, "view");
    GLint pL_location = glGetUniformLocation(LightShader.Program, "projection");
    GLint scaleL_location = glGetUniformLocation(LightShader.Program, "scale");
    // Ambient
    Shader AmbientShader;
    addShader(AmbientShader, "Ambient.shader");
    // set uniforms
    GLint Ambient_m_location = glGetUniformLocation(AmbientShader.Program, "model");
    GLint Ambient_v_location = glGetUniformLocation(AmbientShader.Program, "view");
    GLint Ambient_p_location = glGetUniformLocation(AmbientShader.Program, "projection");
    GLint Ambient_cube_color = glGetUniformLocation(AmbientShader.Program, "cubeColor");
    GLint Ambient_light_color = glGetUniformLocation(AmbientShader.Program, "lightColor");
    // Diffuse
    Shader DiffuseShader;
    addShader(DiffuseShader, "Diffuse.shader");
    // set uniforms
    GLint Diffuse_m_location = glGetUniformLocation(DiffuseShader.Program, "model");
    GLint Diffuse_v_location = glGetUniformLocation(DiffuseShader.Program, "view");
    GLint Diffuse_p_location = glGetUniformLocation(DiffuseShader.Program, "projection");
    GLint Diffuse_cube_color = glGetUniformLocation(DiffuseShader.Program, "cubeColor");
    GLint Diffuse_light_color = glGetUniformLocation(DiffuseShader.Program, "lightColor");
    GLint Diffuse_light_position = glGetUniformLocation(DiffuseShader.Program, "lightPos");
    // Specular
    Shader SpecularShader;
    addShader(SpecularShader, "Specular.shader");
    // set uniforms
    GLint Specular_m_location = glGetUniformLocation(SpecularShader.Program, "model");
    GLint Specular_v_location = glGetUniformLocation(SpecularShader.Program, "view");
    GLint Specular_p_location = glGetUniformLocation(SpecularShader.Program, "projection");
    GLint Specular_cube_color = glGetUniformLocation(SpecularShader.Program, "cubeColor");
    GLint Specular_light_color = glGetUniformLocation(SpecularShader.Program, "lightColor");
    GLint Specular_light_position = glGetUniformLocation(SpecularShader.Program, "lightPos");
    GLint Specular_camera_position = glGetUniformLocation(SpecularShader.Program, "viewPos");
    // Specular
    Shader PhongShader;
    addShader(PhongShader, "Phong.shader");
    // set uniforms
    GLint Phong_m_location = glGetUniformLocation(PhongShader.Program, "model");
    GLint Phong_v_location = glGetUniformLocation(PhongShader.Program, "view");
    GLint Phong_p_location = glGetUniformLocation(PhongShader.Program, "projection");
    GLint Phong_cube_color = glGetUniformLocation(PhongShader.Program, "cubeColor");
    GLint Phong_light_color = glGetUniformLocation(PhongShader.Program, "lightColor");
    GLint Phong_light_position = glGetUniformLocation(PhongShader.Program, "lightPos");
    GLint Phong_camera_position = glGetUniformLocation(PhongShader.Program, "viewPos");
    // Texture
    Shader TextureShader;
    addShader(TextureShader, "Texture.shader");
    // set uniforms
    GLint Texture_m_location = glGetUniformLocation(TextureShader.Program, "model");
    GLint Texture_v_location = glGetUniformLocation(TextureShader.Program, "view");
    GLint Texture_p_location = glGetUniformLocation(TextureShader.Program, "projection");
    // Texture lambert
    Shader TextureLambertShader;
    addShader(TextureLambertShader, "TextureLambert.shader");
    // set uniforms
    GLint TextureLambert_m_location = glGetUniformLocation(TextureLambertShader.Program, "model");
    GLint TextureLambert_v_location = glGetUniformLocation(TextureLambertShader.Program, "view");
    GLint TextureLambert_p_location = glGetUniformLocation(TextureLambertShader.Program, "projection");
    GLint TextureLambert_light_color = glGetUniformLocation(TextureLambertShader.Program, "lightColor");
    GLint TextureLambert_light_position = glGetUniformLocation(TextureLambertShader.Program, "lightPos");
    // set vertex buffer and array object for cubes
    setVertices(VBO, VAO);
    // set vertex array object for light
    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // set vertex array object for ambient
    unsigned int ambientVAO;
    glGenVertexArrays(1, &ambientVAO);
    glBindVertexArray(ambientVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // set vertex array object for diffuse
    unsigned int diffuseVAO;
    glGenVertexArrays(1, &diffuseVAO);
    glBindVertexArray(diffuseVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // set vertex array object for specular
    unsigned int specularVAO;
    glGenVertexArrays(1, &specularVAO);
    glBindVertexArray(specularVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // set vertex array object for phong
    unsigned int phongVAO;
    glGenVertexArrays(1, &phongVAO);
    glBindVertexArray(phongVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // set vertex array object for texture
    unsigned int textureVAO;
    glGenVertexArrays(1, &textureVAO);
    glBindVertexArray(textureVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(9 * sizeof(float)));
    glEnableVertexAttribArray(3);
    // set vertex array object for texture lambert
    unsigned int textureLambertVAO;
    glGenVertexArrays(1, &textureLambertVAO);
    glBindVertexArray(textureLambertVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(9 * sizeof(float)));
    glEnableVertexAttribArray(3);

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        float aspect = (float)width / (float)height;
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        mat4x4 model;
        // view
        vec3 target;
        vec3_add(target, cameraFront, cameraPos);
        mat4 view = LookAtRH(cameraPos, target, cameraUp);
        // projection
        mat4x4 projection;
        mat4x4_perspective(projection, toRadians(fov), aspect, 0.1f, 100.f);
        // cubes
        /*
        glUseProgram(ColorShader.Program);
        glUniformMatrix4fv(v_location, 1, GL_FALSE, (const GLfloat*)view.mat);
        glUniformMatrix4fv(p_location, 1, GL_FALSE, (const GLfloat*)projection);
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 20; i++){
            float x = cubePositions[i][0];
            float y = cubePositions[i][1];
            float z = cubePositions[i][2];
            // model
            mat4x4 model;
            mat4x4_identity(model);
            mat4x4_translate(model, x, y, z);
            glUniformMatrix4fv(m_location, 1, GL_FALSE, (const GLfloat*)model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        */
        // light
        glUseProgram(LightShader.Program);
        glUniformMatrix4fv(vL_location, 1, GL_FALSE, (const GLfloat*)view.mat);
        glUniformMatrix4fv(pL_location, 1, GL_FALSE, (const GLfloat*)projection);
        mat4x4_identity(model);
        mat4x4_translate(model, lightPos[0], lightPos[1], lightPos[2]);
        // scale
        mat4x4 scale;
        mat4x4_identity(scale);
        float scaleValue = 0.5f;
        scale[0][0] = scaleValue;
        scale[1][1] = scaleValue;
        scale[2][2] = scaleValue;
        glUniformMatrix4fv(scaleL_location, 1, GL_FALSE, (const GLfloat*)scale);
        glUniformMatrix4fv(mL_location, 1, GL_FALSE, (const GLfloat*)model);
        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // ambient
        glUseProgram(AmbientShader.Program);
        glUniformMatrix4fv(Ambient_v_location, 1, GL_FALSE, (const GLfloat*)view.mat);
        glUniformMatrix4fv(Ambient_p_location, 1, GL_FALSE, (const GLfloat*)projection);
        mat4x4_identity(model);
        mat4x4_translate(model, ambientPos[0], ambientPos[1], ambientPos[2]);
        glUniformMatrix4fv(Ambient_m_location, 1, GL_FALSE, (const GLfloat*)model);
        glUniform3fv(Ambient_cube_color, 1, cubeCol);
        glUniform3fv(Ambient_light_color, 1, lightCol);
        glBindVertexArray(ambientVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // diffuse
        glUseProgram(DiffuseShader.Program);
        glUniformMatrix4fv(Diffuse_v_location, 1, GL_FALSE, (const GLfloat*)view.mat);
        glUniformMatrix4fv(Diffuse_p_location, 1, GL_FALSE, (const GLfloat*)projection);
        mat4x4_identity(model);
        mat4x4_translate(model, diffusePos[0], diffusePos[1], diffusePos[2]);
        glUniformMatrix4fv(Diffuse_m_location, 1, GL_FALSE, (const GLfloat*)model);
        glUniform3fv(Diffuse_cube_color, 1, cubeCol);
        glUniform3fv(Diffuse_light_color, 1, lightCol);
        glUniform3fv(Diffuse_light_position, 1, lightPos);
        glBindVertexArray(diffuseVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // specular
        glUseProgram(SpecularShader.Program);
        glUniformMatrix4fv(Specular_v_location, 1, GL_FALSE, (const GLfloat*)view.mat);
        glUniformMatrix4fv(Specular_p_location, 1, GL_FALSE, (const GLfloat*)projection);
        mat4x4_identity(model);
        mat4x4_translate(model, specularPos[0], specularPos[1], specularPos[2]);
        glUniformMatrix4fv(Specular_m_location, 1, GL_FALSE, (const GLfloat*)model);
        glUniform3fv(Specular_cube_color, 1, cubeCol);
        glUniform3fv(Specular_light_color, 1, lightCol);
        glUniform3fv(Specular_light_position, 1, lightPos);
        glUniform3fv(Specular_camera_position, 1, cameraPos);
        glBindVertexArray(specularVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // phong
        glUseProgram(PhongShader.Program);
        glUniformMatrix4fv(Phong_v_location, 1, GL_FALSE, (const GLfloat*)view.mat);
        glUniformMatrix4fv(Phong_p_location, 1, GL_FALSE, (const GLfloat*)projection);
        mat4x4_identity(model);
        mat4x4_translate(model, phongPos[0], phongPos[1], phongPos[2]);
        glUniformMatrix4fv(Phong_m_location, 1, GL_FALSE, (const GLfloat*)model);
        glUniform3fv(Phong_cube_color, 1, cubeCol);
        glUniform3fv(Phong_light_color, 1, lightCol);
        glUniform3fv(Phong_light_position, 1, lightPos);
        glUniform3fv(Phong_camera_position, 1, cameraPos);
        glBindVertexArray(phongVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // texture
        glUseProgram(TextureShader.Program);
        glUniformMatrix4fv(Texture_v_location, 1, GL_FALSE, (const GLfloat*)view.mat);
        glUniformMatrix4fv(Texture_p_location, 1, GL_FALSE, (const GLfloat*)projection);
        mat4x4_identity(model);
        mat4x4_translate(model, texturePos[0], texturePos[1], texturePos[2]);
        glUniformMatrix4fv(Texture_m_location, 1, GL_FALSE, (const GLfloat*)model);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(textureVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // texture lambert
        glUseProgram(TextureLambertShader.Program);
        glUniformMatrix4fv(TextureLambert_v_location, 1, GL_FALSE, (const GLfloat*)view.mat);
        glUniformMatrix4fv(TextureLambert_p_location, 1, GL_FALSE, (const GLfloat*)projection);
        mat4x4_identity(model);
        mat4x4_translate(model, textureLambertPos[0], textureLambertPos[1], textureLambertPos[2]);
        glUniformMatrix4fv(TextureLambert_m_location, 1, GL_FALSE, (const GLfloat*)model);
        glUniform3fv(TextureLambert_light_color, 1, lightCol);
        glUniform3fv(TextureLambert_light_position, 1, lightPos);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(textureLambertVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteVertexArrays(1, &ambientVAO);
    glDeleteVertexArrays(1, &diffuseVAO);
    glDeleteVertexArrays(1, &specularVAO);
    glDeleteVertexArrays(1, &phongVAO);
    glDeleteVertexArrays(1, &textureVAO);
    glDeleteVertexArrays(1, &textureLambertVAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(ColorShader.Program);
    glDeleteProgram(LightShader.Program);
    glDeleteProgram(AmbientShader.Program);
    glDeleteProgram(DiffuseShader.Program);
    glDeleteProgram(SpecularShader.Program);
    glDeleteProgram(PhongShader.Program);
    glDeleteProgram(TextureShader.Program);
    glDeleteProgram(TextureLambertShader.Program);
    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window){
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        isObservator = !isObservator;
    }
    if (isObservator == false) {
        float cameraSpeed = 2.5f * deltaTime;
        vec3 moveV;
        moveV[0] = cameraSpeed * cameraFront[0];
        moveV[1] = cameraSpeed * cameraFront[1];
        moveV[2] = cameraSpeed * cameraFront[2];
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            vec3_add(cameraPos, cameraPos, moveV);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            vec3_sub(cameraPos, cameraPos, moveV);
        }
        vec3 moveH;
        vec3_mul_cross(moveH, cameraFront, cameraUp);
        vec3_norm(moveH, moveH);
        moveH[0] = cameraSpeed * moveH[0];
        moveH[1] = cameraSpeed * moveH[1];
        moveH[2] = cameraSpeed * moveH[2];
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            vec3_sub(cameraPos, cameraPos, moveH);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            vec3_add(cameraPos, cameraPos, moveH);
        }
        // move light source
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            vec3_sub(cameraPos, cameraPos, moveH);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            vec3_add(cameraPos, cameraPos, moveH);
        }
    } else if (isObservator == true) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            lightPos[2] -= 0.1f;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            lightPos[2] += 0.1f;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            lightPos[0] -= 0.1f;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            lightPos[0] += 0.1f;
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            lightPos[1] -= 0.1f;
        }
        if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
            lightPos[1] += 0.1f;
        }
    }
}
GLuint setVertexShader(const char* shader, GLuint ShaderReference) {
    // vertex shader
    glShaderSource(ShaderReference, 1, &shader, NULL);
    glCompileShader(ShaderReference);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(ShaderReference, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(ShaderReference, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    return ShaderReference;
}
GLuint setFragmentShader(const char* shader, GLuint ShaderReference) {
    // fragment shader
    glShaderSource(ShaderReference, 1, &shader, NULL);
    glCompileShader(ShaderReference);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(ShaderReference, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(ShaderReference, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    return ShaderReference;
}
GLuint setProgram(GLuint program, GLuint vertex, GLuint fragment) {
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    // check for linking errors
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    return program;
}
void setVertices(GLuint &VBO, GLuint &VAO){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    // position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
    // color attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    // normal attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
}
float dot_product(vec3 v1, vec3 v2) {
    float product = 0;
    for (int i = 0; i < 3; i++) {
        product += v1[i] * v2[i];
    }
    return product;
}
struct mat4 LookAtRH(vec3 eye, vec3 target, vec3 up){
    // The "forward" vector.
    vec3 zaxis;
    vec3_sub(zaxis, eye, target);
    vec3_norm(zaxis, zaxis);    
    // The "right" vector.
    vec3 xaxis;
    vec3_mul_cross(xaxis, up, zaxis);
    vec3_norm(xaxis, xaxis);
    // The "right" vector.
    vec3 yaxis;
    vec3_mul_cross(yaxis, zaxis, xaxis);
    // Create a 4x4 view matrix from the right, up, forward and eye position vectors
    mat4 viewMatrix;
    viewMatrix.mat[0][0] = xaxis[0];
    viewMatrix.mat[0][1] = yaxis[0];
    viewMatrix.mat[0][2] = zaxis[0];
    viewMatrix.mat[0][3] = 0.0f;

    viewMatrix.mat[1][0] = xaxis[1];
    viewMatrix.mat[1][1] = yaxis[1];
    viewMatrix.mat[1][2] = zaxis[1];
    viewMatrix.mat[1][3] = 0.0f;

    viewMatrix.mat[2][0] = xaxis[2];
    viewMatrix.mat[2][1] = yaxis[2];
    viewMatrix.mat[2][2] = zaxis[2];
    viewMatrix.mat[2][3] = 0.0f;
    
    viewMatrix.mat[3][0] = -dot_product(xaxis, eye);
    viewMatrix.mat[3][1] = -dot_product(yaxis, eye);
    viewMatrix.mat[3][2] = -dot_product(zaxis, eye);
    viewMatrix.mat[3][3] = 1.0f;

    return viewMatrix;
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    if (firstMouse){
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = (float)xpos - lastX;
    float yoffset = lastY - (float)ypos;
    lastX = (float)xpos;
    lastY = (float)ypos;
    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    yaw += xoffset;
    pitch += yoffset;
    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }
    vec3 direction;
    direction[0] = cos(toRadians(yaw)) * cos(toRadians(pitch));
    direction[1] = sin(toRadians(pitch));
    direction[2] = sin(toRadians(yaw)) * cos(toRadians(pitch));
    vec3_norm(cameraFront, direction);
}
float toRadians(float degree){
    float pi = (float)3.14159265359;
    return (degree * (pi / 180.0f));
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    fov -= (float)yoffset;
    if (fov < 10.0f) {
        fov = 10.0f;
    }
    if (fov > 120.0f) {
        fov = 120.0f;
    }
}
static ShaderProgramSource ParseShader(const std::string& path) {
    // his idea
    // https://www.youtube.com/watch?v=2pv0Fbo-7ms
    std::ifstream stream;
    try {
        stream.open(path);
    } catch (std::ios_base::failure&) {
        throw std::system_error{ errno, std::generic_category(), path };
    }
    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)){
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        } else {
            ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str(), ss[1].str() };
}
void addShader(Shader &shader, std::string path) {
    ShaderProgramSource colorShaderSource = ParseShader(path);
    shader.Vertex = glCreateShader(GL_VERTEX_SHADER);
    shader.Fragment = glCreateShader(GL_FRAGMENT_SHADER);
    shader.Program = glCreateProgram();
    shader.Vertex = setVertexShader(colorShaderSource.VertexSource.c_str(), shader.Vertex);
    shader.Fragment = setFragmentShader(colorShaderSource.FragmentSource.c_str(), shader.Fragment);
    shader.Program = setProgram(shader.Program, shader.Vertex, shader.Fragment);
}
void deleteShader(Shader& shader) {
    glDeleteShader(shader.Vertex);
    glDeleteShader(shader.Fragment);
}