#pragma once

class GlUtil
{
public:
	GlUtil();
	~GlUtil();

	static int GlCreateShader(int shaderType, const char* shaderSource);

	static int GlLinkShaker(unsigned int glProgram, int vertexShader, int fragmentShader, int geometryShader);
};