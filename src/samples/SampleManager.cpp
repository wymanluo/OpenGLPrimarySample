#include "SampleManager.h"
#include "GLFW/glfw3.h"

#include "HelloTriangle.h"

SampleManager::SampleManager()
	: m_pressKey(-1)
{
	m_helloTriangle = new HelloTriangle();
}

SampleManager::~SampleManager()
{
}

void SampleManager::DrawSample(int pressKey)
{
	if (pressKey != -1 && pressKey != m_pressKey)
	{
		m_pressKey = pressKey;
	}
	if (m_pressKey == GLFW_KEY_1)
	{
		m_helloTriangle->Draw();
	}
}