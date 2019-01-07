#pragma once

class HelloTriangle;

class SampleManager
{
public:
	SampleManager();
	~SampleManager();

	void DrawSample(int pressKey);

private:
	int m_pressKey;
	HelloTriangle* m_helloTriangle;
};