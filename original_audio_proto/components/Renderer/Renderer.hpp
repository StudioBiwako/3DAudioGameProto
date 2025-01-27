// Renderer.hpp
#pragma once

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/gl3.h>
#endif

#include <vector>

struct Triangle
{
    float x, y;    // position
    float r, g, b; // color
    float scale;   // size multiplier
};

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void setupTriangle();
    void render();

    // New methods to manage triangles
    void addTriangle(float x, float y, float r = 1.0f, float g = 0.0f, float b = 0.0f, float scale = 1.0f);
    void clearTriangles();

private:
    GLuint compileShader(GLenum type, const char *source);

    GLuint shaderProgram;
    GLuint VAO;
    GLuint VBO;

    const char *vertexShaderSource;
    const char *fragmentShaderSource;

    std::vector<Triangle> triangles;
};