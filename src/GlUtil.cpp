#include "GlUtil.h"
#include "glad/glad.h"
#include <iostream>

int GlUtil::GlCompileShader(int shader, const char* shaderSource)
{
	glShaderSource(shader, 1, &shaderSource, nullptr);
	glCompileShader(shader);
	
	char errorInfo[256] = { 0 };
	int ret;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &ret);
	if (!ret)
	{
		glGetShaderInfoLog(shader, sizeof(errorInfo), nullptr, errorInfo);
		std::cout << "[Error]compile shader fail! info:" << errorInfo << std::endl;
		return 0;
	}

	return 1;
}

int GlUtil::GlLinkShaker(unsigned int glProgram, int vertexShader, int fragmentShader)
{
	glAttachShader(glProgram, vertexShader);
	glAttachShader(glProgram, fragmentShader);
	glLinkProgram(glProgram);

	char errorInfo[256] = { 0 };
	int ret;
	glGetProgramiv(glProgram, GL_LINK_STATUS, &ret);
	if (!ret)
	{
		glGetProgramInfoLog(glProgram, sizeof(errorInfo), nullptr, errorInfo);
		std::cout << "[Error]link program fail! info:" << errorInfo << std::endl;
		return 0;
	}

	return 1;
}