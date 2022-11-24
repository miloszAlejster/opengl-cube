#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "linmath.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>

const float cubeVertices[] = {
    // position         // color
    -0.5f, -0.5f, -0.5f, 0.9f, 0.1f, 0.9f,
    0.5f, -0.5f, -0.5f, 0.9f, 0.1f, 0.9f,
    0.5f, 0.5f, -0.5f, 0.9f, 0.1f, 0.9f,
    0.5f, 0.5f, -0.5f, 0.9f, 0.1f, 0.9f,
    -0.5f, 0.5f, -0.5f, 0.9f, 0.1f, 0.9f,
    -0.5f, -0.5f, -0.5f, 0.9f, 0.1f, 0.9f,
    -0.5f, -0.5f, 0.5f, 0.5f, 0.3f, 0.7f,
    0.5f, -0.5f, 0.5f, 0.5f, 0.3f, 0.7f,
    0.5f, 0.5f, 0.5f, 0.5f, 0.3f, 0.7f,
    0.5f, 0.5f, 0.5f, 0.5f, 0.3f, 0.7f,
    -0.5f, 0.5f, 0.5f, 0.5f, 0.3f, 0.7f,
    -0.5f, -0.5f, 0.5f, 0.5f, 0.3f, 0.7f,
    -0.5f, 0.5f, 0.5f, 0.2f, 0.4f, 0.7f,
    -0.5f, 0.5f, -0.5f, 0.2f, 0.4f, 0.7f,
    -0.5f, -0.5f, -0.5f, 0.2f, 0.4f, 0.7f,
    -0.5f, -0.5f, -0.5f, 0.2f, 0.4f, 0.7f,
    -0.5f, -0.5f, 0.5f, 0.2f, 0.4f, 0.7f,
    -0.5f, 0.5f, 0.5f, 0.2f, 0.4f, 0.7f,
    0.5f, 0.5f, 0.5f, 0.5f, 0.1f, 0.1f,
    0.5f, 0.5f, -0.5f, 0.5f, 0.1f, 0.1f,
    0.5f, -0.5f, -0.5f, 0.5f, 0.1f, 0.1f,
    0.5f, -0.5f, -0.5f, 0.5f, 0.1f, 0.1f,
    0.5f, -0.5f, 0.5f, 0.5f, 0.1f, 0.1f,
    0.5f, 0.5f, 0.5f, 0.5f, 0.1f, 0.1f,
    -0.5f, -0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.5f, 0.0f, 9.0f,
    0.5f, 0.5f, -0.5f, 0.5f, 0.0f, 9.0f,
    0.5f, 0.5f, 0.5f, 0.5f, 0.0f, 9.0f,
    0.5f, 0.5f, 0.5f, 0.5f, 0.0f, 9.0f,
    -0.5f, 0.5f, 0.5f, 0.5f, 0.0f, 9.0f,
    -0.5f, 0.5f, -0.5f, 0.5f, 0.0f, 9.0f
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
int main(void) {
    GLFWwindow* window;
    GLuint VBO, VAO;
    GLint m_location, v_location, p_location;
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
    // init shaders
    Shader ColorShader;
    addShader(ColorShader, "Colors.shader");
    // set uniforms
    m_location = glGetUniformLocation(ColorShader.Program, "model");
    v_location = glGetUniformLocation(ColorShader.Program, "view");
    p_location = glGetUniformLocation(ColorShader.Program, "projection");
    // clear shaders
    deleteShader(ColorShader);
    // set vertex buffer and array object
    setVertices(VBO, VAO);

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
        glUseProgram(ColorShader.Program);
        mat4x4 model, projection;
        mat4 view;
        // view
        vec3 target;
        vec3_add(target, cameraFront, cameraPos);
        view = LookAtRH(cameraPos, target, cameraUp);
        glUniformMatrix4fv(v_location, 1, GL_FALSE, (const GLfloat*)view.mat);
        // projection
        mat4x4_perspective(projection, toRadians(fov), aspect, 0.1f, 100.f);
        glUniformMatrix4fv(p_location, 1, GL_FALSE, (const GLfloat*)projection);
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 20; i++){
            float x = cubePositions[i][0];
            float y = cubePositions[i][1];
            float z = cubePositions[i][2];
            // model
            mat4x4_identity(model);
            mat4x4_translate(model, x, y, z);
            glUniformMatrix4fv(m_location, 1, GL_FALSE, (const GLfloat*)model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(ColorShader.Program);
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    // color attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
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