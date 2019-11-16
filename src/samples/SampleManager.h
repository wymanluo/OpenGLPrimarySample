#pragma once

#include <unordered_map>

class SampleBase;

class SampleManager
{
public:
    enum ENUM_SAMPLE_TYPE
    {
        ENUM_SAMPLE_TRIANGLE,
        ENUM_SAMPLE_GEOMETRY,
        ENUM_SAMPLE_TYPE_NUM,
    };

public:
	SampleManager();
	~SampleManager();

	void DrawSample(int pressKey);

private:
    void InitSample();

    SampleBase* GetSample(int type);

private:
	int pressKey_;
    std::unordered_map<int, SampleBase*> samples_;
};