#include "SampleBase.h"
#include "GlUtil.h"
#include "glad/glad.h"

SampleBase::SampleBase(const GLchar* vertexShader, const GLchar* fragmentShader, const GLchar* geometryShader)
    : shaderVertex_(-1)
    , shaderFragment_(-1)
    , shaderGeometry_(-1)
    , shaderProgram_(-1)
{
    InitShader(vertexShader, fragmentShader, geometryShader);
}

SampleBase::~SampleBase()
{
}

void SampleBase::InitShader(const GLchar* vertexShader, const GLchar* fragmentShader, const GLchar* geometryShader)
{
    shaderVertex_ = GlUtil::GlCreateShader(GL_VERTEX_SHADER, vertexShader);
    shaderFragment_ = GlUtil::GlCreateShader(GL_FRAGMENT_SHADER, fragmentShader);
    if (geometryShader != nullptr)
    {
        shaderGeometry_ = GlUtil::GlCreateShader(GL_GEOMETRY_SHADER, geometryShader);
    }
    shaderProgram_ = glCreateProgram();
    GlUtil::GlLinkShaker(shaderProgram_, shaderVertex_, shaderFragment_, shaderGeometry_);
}

void SampleBase::Draw()
{
    glBindVertexArray(VAO_);
    glUseProgram(shaderProgram_);
}