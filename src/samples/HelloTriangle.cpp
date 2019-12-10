#include "HelloTriangle.h"
#include "shader/Shader.h"
#include "GLFW/glfw3.h"

#include <iostream>

HelloTriangle::HelloTriangle()
{
    InitShader(hello_triangle_vs, hello_triangle_fs, nullptr);
}

HelloTriangle::~HelloTriangle()
{
}

void HelloTriangle::Init() 
{
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // left  
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // right 
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // top   
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

void HelloTriangle::OnKeyPress(int key, float delta)
{
}

void HelloTriangle::Draw()
{
    __super::Draw();
   
    /*double time  = glfwGetTime();
    GLfloat red   = std::sin(time);
    GLfloat green = std::cos(time);
    GLfloat blue  = std::tan(time);
    int uniformColorIndex = glGetUniformLocation(shaderProgram_, "uniformColor");
    glUniform4f(uniformColorIndex, red, green, blue, 1.0f);*/

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}