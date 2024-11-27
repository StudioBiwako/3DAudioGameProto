#pragma once

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/gl3.h>
#endif

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void setupTriangle();
    void render();

private:
    GLuint compileShader(GLenum type, const char *source);

    GLuint shaderProgram;
    GLuint VAO;
    const char *vertexShaderSource;
    const char *fragmentShaderSource;
};