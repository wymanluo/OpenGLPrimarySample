#pragma once
#include "SampleBase.h"

class GeometryShader : public SampleBase
{
public:
    GeometryShader();
    virtual ~GeometryShader();

public:
    void Init() override;
    void Draw() override;
};

