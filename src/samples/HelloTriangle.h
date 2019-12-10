#pragma once
#include "SampleBase.h"

class HelloTriangle : public SampleBase
{
public:
	HelloTriangle();
	virtual ~HelloTriangle();

public:
    void Init() override;
	void Draw() override;	
    void OnKeyPress(int key, float delta) override;
};