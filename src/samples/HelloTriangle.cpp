#include "HelloTriangle.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "GlUtil.h"
#include "Shader.h"
#include <iostream>

HelloTriangle::HelloTriangle()
{
	Init();
}

HelloTriangle::~HelloTriangle()
{
}

void HelloTriangle::Init() 
{
	// vertex shader
	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GlUtil::GlCompileShader(m_vertexShader, shader_hello_triangle_vert);

	// fragment shader
	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	GlUtil::GlCompileShader(m_fragmentShader, shader_hello_triangle_frag);

	// link shaders
	m_shaderProgram = glCreateProgram();
	GlUtil::GlLinkShaker(m_shaderProgram, m_vertexShader, m_fragmentShader);
	
	//glDeleteShader(m_vertexShader);
	//glDeleteShader(m_fragmentShader);

	// vertex position data
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // left  
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // right 
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // top   
	};

	// vertex array object
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	// vertex buffer object
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glUseProgram(m_shaderProgram);

	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void HelloTriangle::Draw()
{
	float time  = glfwGetTime();
	float red   = std::sin(time);
	float green = std::cos(time);
	float blue  = std::tan(time);
    /*float red = 1.0f;
    float green = 0.5f;
    float blue = 0.0f;*/
	int uniformColorIndex = glGetUniformLocation(m_shaderProgram, "uniformColor");
	glUniform4f(uniformColorIndex, red, green, blue, 1.0f);

	glBindVertexArray(m_VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawArrays(GL_TRIANGLES, 0, 3);
	//glBindVertexArray(0); // no need to unbind it every time a
}