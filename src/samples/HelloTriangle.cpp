#include "HelloTriangle.h"
#include "glad/glad.h"
#include "GlUtil.h"
#include <iostream>

HelloTriangle::HelloTriangle()
{
	Init();
}

HelloTriangle::~HelloTriangle()
{
}

static const char *g_vertexShaderSource = "#version 450 core\n"
"layout (location = 0) in vec3 pos;"
"void main()"
"{"
"	gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);"
"}";

static const char *g_fragmentShaderSource = "#version 450 core\n"
"out vec4 FragColor;"
"void main()"
"{"
"   FragColor = vec4(0, 0.75, 1.0f, 1.0f);"
"}";

void HelloTriangle::Init() 
{
	// vertex shader
	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GlUtil::GlCompileShader(m_vertexShader, g_vertexShaderSource);

	// fragment shader
	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	GlUtil::GlCompileShader(m_fragmentShader, g_fragmentShaderSource);

	// link shaders
	m_shaderProgram = glCreateProgram();
	GlUtil::GlLinkShaker(m_shaderProgram, m_vertexShader, m_fragmentShader);
	
	glDeleteShader(m_vertexShader);
	glDeleteShader(m_fragmentShader);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		0.5f, -0.5f, 0.0f, // right 
		0.0f,  0.5f, 0.0f  // top   
	};

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// uncomment this call to draw in wireframe polygons.
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void HelloTriangle::Draw()
{
	// draw our first triangle
	glUseProgram(m_shaderProgram);
	glBindVertexArray(m_VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0); // no need to unbind it every time 
}