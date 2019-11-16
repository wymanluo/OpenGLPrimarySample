#include "GeometryShader.h"
#include "shader/Shader.h"

GeometryShader::GeometryShader()
    : SampleBase(shader_geometry_shader_vert, 
        shader_geometry_shader_frag,
        shader_geometry_shader_geom)
{
}

GeometryShader::~GeometryShader()
{
}

void GeometryShader::Init()
{
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,   
    };

    glGenVertexArrays(1, &VAO_);
    glBindVertexArray(VAO_);

    glGenBuffers(1, &VBO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void GeometryShader::Draw()
{
    __super::Draw();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glDrawArrays(GL_POINTS, 0, 3);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}