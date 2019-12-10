#pragma once

#include "glad/glad.h"

class Shader;

class SampleBase
{
public:
    SampleBase();
    virtual ~SampleBase();

public:
    virtual void Init() = 0;
    virtual void Draw();
    virtual void OnKeyPress(int key, float delta) = 0;
    virtual void OnMouseMove(double x, double y) {}
    virtual void OnMouseScroll(double x, double y) {}

protected:
    void InitShader(const GLchar* vertexShader, const GLchar* fragmentShader, const GLchar* geometryShader);
    Shader* GetShader() const {return shader_;}

protected:
    unsigned int VBO_;
    unsigned int VAO_;
    Shader* shader_;
};