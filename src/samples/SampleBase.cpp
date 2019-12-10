#include "SampleBase.h"
#include "GlUtil.h"
#include "glad/glad.h"
#include "shader/Shader.h"

SampleBase::SampleBase()
    : shader_(nullptr)
{
}

SampleBase::~SampleBase()
{
    delete shader_;
}

void SampleBase::InitShader(const GLchar* vertexShader, const GLchar* fragmentShader, const GLchar* geometryShader)
{
    shader_ = new Shader(vertexShader, fragmentShader, geometryShader);
}

void SampleBase::Draw()
{
    glBindVertexArray(VAO_);
    shader_->use();
    //glUseProgram(shaderProgram_);
}