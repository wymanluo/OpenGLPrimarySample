#include "GlUtil.h"
#include "glad/glad.h"
#include <iostream>

int GlUtil::GlCreateShader(int shaderType, const char* shaderSource)
{
    int shader = glCreateShader(shaderType);
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

	return shader;
}

int GlUtil::GlLinkShaker(unsigned int glProgram, int vertexShader, int fragmentShader, int geometryShader)
{
	glAttachShader(glProgram, vertexShader);
	glAttachShader(glProgram, fragmentShader);
    if (geometryShader != -1)
    {
        glAttachShader(glProgram, geometryShader);
    }
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