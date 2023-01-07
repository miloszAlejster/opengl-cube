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
#include <string>
#include "objLoader.cpp"
#include "materialLoader.cpp"
#include "shader.h"
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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
GLuint setVertexShader(const char* shader, GLuint shaderReference);
GLuint setFragmentShader(const char* shader, GLuint shaderReference);
GLuint setProgram(GLuint program, GLuint vertex, GLuint fragment);
void setVertices(GLuint &VBO, GLuint &VAO);
void mouse_callback(GLFWwindow* window, double x, double y);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
static void error_callback(int error, const char* description);
struct mat4 LookAtRH(vec3 eye, vec3 target, vec3 up);
struct mat4 {
    mat4x4 mat;
};
float toRadians(float degree);
void init();

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
GLFWwindow* window;

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
bool isObservator = false;
vec3 lightCol = { 1.0f, 1.0f, 1.0f };
// objs positions
vec3 lightPos = { 3.0f, 2.0f, -1.0f };
vec3 objecttPos = { 0.0f, 0.0f, -1.0f };
// texture
int txWidth, txHeight, nrChannels;
unsigned char* texture_data = stbi_load("resources/fabric.png", &txWidth, &txHeight, &nrChannels, 0);
int main(void) {
    init();
    GLuint VBO_object, VAO, EBO;
    std::vector<Vectors> vectices;
    std::vector<Material> materials;
    std::string materialPath;
    std::vector<int> faceIndex;
    objLoader("resources/monkey.obj", vectices, materialPath, faceIndex);
    materialLoader(materialPath, materials);
    //std::cout << faceIndex.size() << std::endl;
    // texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, txWidth, txHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(texture_data);
    Shader MaterialShader("src/shaders/Material.shader");
    // set vertex buffer object
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO_object);
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_object);
    glBufferData(GL_ARRAY_BUFFER, vectices.size() * sizeof(Vectors), &vectices.front(), GL_STATIC_DRAW);
    // nie dzia³a jeszcze
    // rozumiem, ¿e problem le¿y w objLoader, ale nie zd¹¿y³em zaimlementowaæ sprawdzania powtórzeñ faców
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, faceIndex.size() * sizeof(int), &faceIndex.front(), GL_STATIC_DRAW);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vectors), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vectors), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vectors), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // render
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
        // view
        vec3 target;
        vec3_add(target, cameraFront, cameraPos);
        mat4 view = LookAtRH(cameraPos, target, cameraUp);
        // projection
        mat4x4 projection;
        mat4x4_perspective(projection, toRadians(fov), aspect, 0.1f, 100.f);
        // model
        mat4x4 model;
        mat4x4_identity(model);
        mat4x4_translate(model, objecttPos[0], objecttPos[1], objecttPos[2]);
        // shader
        MaterialShader.use();
        MaterialShader.setMat4("view", view.mat);
        MaterialShader.setMat4("projection", projection);
        MaterialShader.setMat4("model", model);
        MaterialShader.setVec3("lightPos", lightPos);
        MaterialShader.setVec3("lightCol", lightCol);
        MaterialShader.setVec3("material.ambient", materials[0].ambient);
        MaterialShader.setVec3("material.diffuse", materials[0].diffuse);
        MaterialShader.setVec3("material.specular", materials[0].specular);
        MaterialShader.setFloat("material.shininess", materials[0].shininess);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, vectices.size());
        // nie dzia³a jeszcze
        /*glDrawElements(GL_TRIANGLES, faceIndex.size(), GL_UNSIGNED_INT, 0);*/
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO_object);
    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        isObservator = !isObservator;
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}
static void error_callback(int error, const char* description){
    fprintf(stderr, "Error: %s\n", description);
}
void processInput(GLFWwindow* window){
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
void init() {
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
    glfwSetKeyCallback(window, key_callback);
    // config
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    gladLoadGL();
    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);
}
