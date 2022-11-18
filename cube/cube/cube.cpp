#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "linmath.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

float cubeVertices[] = {
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
    -0.5f, 0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.5f, 0.0f, 0.0f
};
vec3 cubePositions[] = {
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 1.0f},
    {-1.5f, -2.2f, -2.5f},
    {-3.8f, -2.0f, -12.3f},
    {2.4f, -0.4f, -3.5f},
    {-1.7f, 3.0f, -7.5f},
    {1.3f, -2.0f, -2.5f},
    {1.5f, 2.0f, -2.5f},
    {1.5f, 0.2f, -1.5f},
    {-1.3f, 1.0f, -1.5f}
};
const char* vertex_shader_cube =
"#version 330 core\n"
"uniform mat4 model;\n"
"uniform mat4 projection;\n"
"uniform mat4 view;\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 vertexColor;\n"
"void main()\n"
"{\n" 
"    gl_Position = model * projection * view * vec4(aPos, 1.0f);\n"
"    vertexColor = aColor;\n"
"}\n";

const char* fragment_shader_cube =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 vertexColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(vertexColor, 1.0f);\n"
"}\n";

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}
void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
unsigned int setVertexShader(const char* shader, unsigned int shaderReference);
unsigned int setFragmentShader(const char* shader, unsigned int shaderReference);
unsigned int setProgram(unsigned int program, unsigned int vertex, unsigned int fragment);
void setVertices(unsigned int &VBO, unsigned int &VAO);
void mouse_callback(GLFWwindow* window, double x, double y);
struct mat4 LookAtRH(vec3 eye, vec3 target, vec3 up);
struct mat4 {
    mat4x4 mat;
};
float toRadians(float degree);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
vec3 cameraPos = { 0.0f, 0.0f, -3.0f };
vec3 cameraUp = { 0.0f, 1.0f, 0.0f };
vec3 cameraFront = { 0.0f, 0.0f, -1.0f };
vec3 up = { 0.0f, 1.0f, 0.0f };
mat4 view;
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
    GLuint vertex_buffer, vertex_shader, fragment_shader, program;
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
    // config
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    gladLoadGL();
    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);
    // init shaders
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    vertexShader = setVertexShader(vertex_shader_cube, vertexShader);
    fragmentShader = setFragmentShader(fragment_shader_cube, fragmentShader);
    // init program
    unsigned int shaderProgram = glCreateProgram();
    shaderProgram = setProgram(shaderProgram, vertexShader, fragmentShader);
    // set uniforms
    m_location = glGetUniformLocation(shaderProgram, "model");
    v_location = glGetUniformLocation(shaderProgram, "view");
    p_location = glGetUniformLocation(shaderProgram, "projection");
    // clear shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    // set vertex buffer and array object
    unsigned int VBO, VAO;
    setVertices(VBO, VAO);

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = (float)width / (float)height;        
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProgram);
        mat4x4 model, projection;
        // view
        vec3 target;
        vec3_add(target, cameraFront, cameraPos);
        view = LookAtRH(cameraPos, target, cameraUp);
        glUniformMatrix4fv(v_location, 1, GL_FALSE, (const GLfloat*)view.mat);
        // projection
        mat4x4_ortho(projection, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glUniformMatrix4fv(p_location, 1, GL_FALSE, (const GLfloat*)projection);
        // pass transform to shader
        glBindVertexArray(VAO);
        for (int i = 0; i < 10; i++){
            float x = cubePositions[i][0];
            float y = cubePositions[i][1];
            float z = cubePositions[i][2];
            //std::cout << x << " " << y << " " << z << "\n";
            mat4x4_translate(model, x, y, z);
            mat4x4_rotate(model, model, 0.1f, 0.1f, 0.1f, 1.0f);
            glUniformMatrix4fv(m_location, 1, GL_FALSE, (const GLfloat*)model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
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
        std::cout << "W\n";
        vec3_add(cameraPos, cameraPos, moveV);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        std::cout << "S\n";
        vec3_sub(cameraPos, cameraPos, moveV);
    }
    vec3 moveH;
    vec3_mul_cross(moveH, cameraFront, cameraUp);
    vec3_norm(moveH, moveH);
    moveH[0] = cameraSpeed * moveH[0];
    moveH[1] = cameraSpeed * moveH[1];
    moveH[2] = cameraSpeed * moveH[2];
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        std::cout << "A\n";
        vec3_sub(cameraPos, cameraPos, moveH);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        std::cout << "D\n";
        vec3_add(cameraPos, cameraPos, moveH);
    }
}
unsigned int setVertexShader(const char* shader, unsigned int ShaderReference) {
    // vertex shader
    glShaderSource(ShaderReference, 1, &vertex_shader_cube, NULL);
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
unsigned int setFragmentShader(const char* shader, unsigned int ShaderReference) {
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
unsigned int setProgram(unsigned int program, unsigned int vertex, unsigned int fragment) {
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
void setVertices(unsigned int &VBO, unsigned int &VAO){
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
    vec3_norm(yaxis, yaxis);
    // Create a 4x4 view matrix from the right, up, forward and eye position vectors
    mat4 viewMatrix;
    viewMatrix.mat[0][0] = xaxis[0];
    viewMatrix.mat[0][1] = yaxis[0];
    viewMatrix.mat[0][2] = zaxis[0];
    viewMatrix.mat[0][3] = 0;

    viewMatrix.mat[1][0] = xaxis[1];
    viewMatrix.mat[1][1] = yaxis[1];
    viewMatrix.mat[1][2] = zaxis[1];
    viewMatrix.mat[1][3] = 0;

    viewMatrix.mat[2][0] = xaxis[2];
    viewMatrix.mat[2][1] = yaxis[2];
    viewMatrix.mat[2][2] = zaxis[2];
    viewMatrix.mat[2][3] = 0;
    
    viewMatrix.mat[3][0] = -dot_product(xaxis, eye);
    viewMatrix.mat[3][1] = -dot_product(yaxis, eye);
    viewMatrix.mat[3][2] = -dot_product(zaxis, eye);
    viewMatrix.mat[3][3] = 1;

    return viewMatrix;
}
void mouse_callback(GLFWwindow* window, double x, double y){
    float xpos = x;
    float ypos = y;
    if (firstMouse){
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
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
    direction[0] = cos((toRadians(yaw)) * cos(toRadians(pitch)));
    direction[1] = sin(toRadians(pitch));
    direction[2] = sin(toRadians(yaw) * cos(toRadians(pitch)));
    vec3_norm(cameraFront, direction);
}
float toRadians(float degree){
    float pi = (float)3.14159265359;
    return (degree * (pi / 180.0f));
}
