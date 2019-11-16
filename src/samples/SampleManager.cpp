#include "SampleManager.h"
#include "GLFW/glfw3.h"

#include "HelloTriangle.h"
#include "GeometryShader.h"

SampleManager::SampleManager()
	: pressKey_(-1)
{
    InitSample();
}

SampleManager::~SampleManager()
{
    for (auto itor = samples_.begin(), itorEnd = samples_.end(); itor != itorEnd; ++itor)
    {
        if (itor->second != nullptr)
        {
            delete itor->second;
        }
    }
    samples_.clear();
}

void SampleManager::InitSample()
{
    for (int i = 0; i < ENUM_SAMPLE_TYPE_NUM; ++i)
    {
        SampleBase* sample = nullptr;
        if (i == ENUM_SAMPLE_TRIANGLE)
        {
            sample = new HelloTriangle();
        }
        else if (i == ENUM_SAMPLE_GEOMETRY)
        {
            sample = new GeometryShader();
        }
        if (sample)
        {
            sample->Init();
            samples_.insert(std::make_pair(i, sample));
        }
    }
}

void SampleManager::DrawSample(int pressKey)
{
	if (pressKey != -1 && pressKey != pressKey_)
	{
        pressKey_ = pressKey;
	}
	if (pressKey_ == GLFW_KEY_1)
	{
        GetSample(ENUM_SAMPLE_TRIANGLE)->Draw();
	}
    else if (pressKey_ == GLFW_KEY_2)
    {
        GetSample(ENUM_SAMPLE_GEOMETRY)->Draw();
    }
}

SampleBase* SampleManager::GetSample(int type)
{
    auto itr = samples_.find(type);
    return itr != samples_.end() ? itr->second : nullptr;
}