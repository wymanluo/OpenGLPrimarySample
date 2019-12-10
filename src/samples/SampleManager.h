#pragma once

#include <unordered_map>
#include "GLFW/glfw3.h"

class SampleBase;

class SampleManager
{
public:
	SampleManager();
	~SampleManager();

	void Draw(int pressKey);
    void KeyPress(int pressKey, float delta);
    void OnMouse(double x, double y);
    void OnScroll(double x, double y);

private:
    void InitSample();

    SampleBase* GetSample(int type);

private:
    int pressKey_;
    std::unordered_map<int, SampleBase*> samples_;
};