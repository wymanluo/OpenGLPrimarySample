#include "SampleManager.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include "HelloTriangle.h"
#include "SampleGeometryShader.h"

enum ENUM_SAMPLE_TYPE
{
    ENUM_SAMPLE_TRIANGLE,
    ENUM_SAMPLE_GEOMETRY,
    ENUM_SAMPLE_TYPE_NUM,
};

SampleManager::SampleManager()
    : pressKey_(GLFW_KEY_2)
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
            sample = new SampleGeometryShader();
        }
        if (sample)
        {
            sample->Init();
            samples_.insert(std::make_pair(i, sample));
        }
    }
}

void SampleManager::Draw(int pressKey)
{
    if (pressKey == GLFW_KEY_1 || pressKey == GLFW_KEY_2)
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
    else
    {
        std::cout << "Error: SampleManager draw nothing" << std::endl;
    }
}

void SampleManager::KeyPress(int pressKey, float delta) 
{
    for (auto itor = samples_.begin(), itorEnd = samples_.end(); itor != itorEnd; ++itor)
    {
        if (itor->second != nullptr)
        {
            itor->second->OnKeyPress(pressKey, delta);
        }
    }
}

SampleBase* SampleManager::GetSample(int type)
{
    auto itr = samples_.find(type);
    return itr != samples_.end() ? itr->second : nullptr;
}

void SampleManager::OnMouse(double x, double y)
{
    for (auto itor = samples_.begin(), itorEnd = samples_.end(); itor != itorEnd; ++itor)
    {
        if (itor->second != nullptr)
        {
            itor->second->OnMouseMove(x, y);
        }
    }
}

void SampleManager::OnScroll(double x, double y)
{
    for (auto itor = samples_.begin(), itorEnd = samples_.end(); itor != itorEnd; ++itor)
    {
        if (itor->second != nullptr)
        {
            itor->second->OnMouseScroll(x, y);
        }
    }
}