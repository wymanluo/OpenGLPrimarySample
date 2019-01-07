#pragma once
class HelloTriangle
{
public:
	HelloTriangle();
	~HelloTriangle();

public:
	void Draw();

private:
	void Init();

private:
	int m_vertexShader;
	int m_fragmentShader;
	int m_shaderProgram;
	unsigned int m_VBO;
	unsigned int m_VAO;
};