#pragma once

class GlUtil
{
public:
	GlUtil();
	~GlUtil();

	static int GlCompileShader(int shader, const char* shaderSource);

	static int GlLinkShaker(unsigned int glProgram, int vertexShader, int fragmentShader);
};