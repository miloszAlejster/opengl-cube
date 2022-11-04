#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "linmath.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

float cubeVertices[] = {
    // pos              // col
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

const char* vertex_shader_cube =
"#version 330 core\n"
"uniform mat4 MVP;\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 vertexColor;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(aPos, 1.0);\n"
"    vertexColor = aColor;\n"
"}\n";

const char* fragment_shader_cube =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 vertexColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(vertexColor, 1.0);\n"
"}\n";

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
unsigned int setVertexShader(const char* shader, unsigned int shaderReference);
unsigned int setFragmentShader(const char* shader, unsigned int shaderReference);
unsigned int setProgram(unsigned int program, unsigned int vertex, unsigned int fragment);
void setVertices(unsigned int &VBO, unsigned int &VAO);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
int main(void) {
    GLFWwindow* window;
    GLuint vertex_buffer, vertex_shader, fragment_shader, program;
    GLint mvp_location;
    glfwSetErrorCallback(error_callback);
    // init glfw
    if (!glfwInit()) exit(EXIT_FAILURE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // create window
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Cube", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
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
    // set uniform
    mvp_location = glGetUniformLocation(shaderProgram, "MVP");
    // clear shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    // set vertex buffer and array object
    unsigned int VBO, VAO;
    setVertices(VBO, VAO);

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

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);
        // create transformation
        mat4x4 m, p, mvp;
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float)height;
        /*
            mat4x4_identity(m);
            // move cube
            mat4x4_translate(m, (float)glfwGetTime() * 0.3f, 0.f, 0.f);
            // rotate cube
            mat4x4_rotate(m, m, 0.2f, 0.4f, 0.06f, (float)glfwGetTime());
            mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
            mat4x4_mul(mvp, p, m);
        */
        // pass transform to shader
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++){
            float x = *cubePositions[i];
            float y = *(cubePositions[i] + 1);
            float z = *(cubePositions[i] + 2);
            //std::cout << x <<" "<< y<<" "<< z<<"\n";
            mat4x4_identity(m);
            mat4x4_translate(m, x, y, z);
            mat4x4_rotate(m, m, 0.2f, 0.4f, 0.06f, (float)glfwGetTime());
            mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
            mat4x4_mul(mvp, p, m);
            glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)mvp);
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
