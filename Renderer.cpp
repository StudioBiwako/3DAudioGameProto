// Renderer.cpp
#include "Renderer.hpp"
#include <iostream>

Renderer::Renderer()
{
    vertexShaderSource = R"(
        #version 150 core
        in vec3 position;
        uniform vec2 offset;
        uniform float scale;
        
        void main() {
            vec3 scaled = position * scale;
            gl_Position = vec4(scaled.x + offset.x, scaled.y + offset.y, scaled.z, 1.0);
        }
    )";

    fragmentShaderSource = R"(
        #version 150 core
        uniform vec3 color;
        out vec4 fragColor;
        
        void main() {
            fragColor = vec4(color, 1.0);
        }
    )";
}

Renderer::~Renderer()
{
    glDeleteProgram(shaderProgram);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

GLuint Renderer::compileShader(GLenum type, const char *source)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "Shader compilation failed: " << infoLog << std::endl;
    }
    return shader;
}

void Renderer::setupTriangle()
{
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Shader program linking failed: " << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Base triangle vertices (smaller default size)
    float vertices[] = {
        -0.1f, -0.1f, 0.0f, // Left
        0.1f, -0.1f, 0.0f,  // Right
        0.0f, 0.1f, 0.0f    // Top
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(posAttrib);
}

void Renderer::addTriangle(float x, float y, float r, float g, float b, float scale)
{
    Triangle t{x, y, r, g, b, scale};
    triangles.push_back(t);
}

void Renderer::clearTriangles()
{
    triangles.clear();
}

void Renderer::render()
{
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);

    // Get uniform locations
    GLint offsetLoc = glGetUniformLocation(shaderProgram, "offset");
    GLint colorLoc = glGetUniformLocation(shaderProgram, "color");
    GLint scaleLoc = glGetUniformLocation(shaderProgram, "scale");

    // Render each triangle with its position and color
    for (const auto &triangle : triangles)
    {
        glUniform2f(offsetLoc, triangle.x, triangle.y);
        glUniform3f(colorLoc, triangle.r, triangle.g, triangle.b);
        glUniform1f(scaleLoc, triangle.scale);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
}