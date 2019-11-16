#pragma once

#include "glad/glad.h"

class SampleBase
{
public:
    SampleBase(const GLchar* vertexShader, const GLchar* fragmentShader, const GLchar* geometryShader);
    virtual ~SampleBase();

public:
    virtual void Init() = 0;
    virtual void Draw();

private:
  void InitShader(const GLchar* vertexShader, const GLchar* fragmentShader, const GLchar* geometryShader);


protected:
    unsigned int VBO_;
    unsigned int VAO_;
    int shaderProgram_;

private:
    int shaderVertex_;
    int shaderFragment_;
    int shaderGeometry_;
};