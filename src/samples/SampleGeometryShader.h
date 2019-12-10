#pragma once
#include "SampleBase.h"

class Model;
class Camera;
class Shader;

class SampleGeometryShader : public SampleBase
{
public:
    SampleGeometryShader();
    virtual ~SampleGeometryShader();

public:
    void Init() override;
    void Draw() override;
    void OnKeyPress(int key, float delta) override;
    void OnMouseMove(double x, double y) override;
    void OnMouseScroll(double x, double y) override;

private:
    void InitVertex();
    void InitExpodeModel();
    void InitModel();
    void DrawPrimitive();
    void DrawExpodeModel();
    void DrawModel();
    float GetNormalScale() const;

private:
    int type_;
    bool pause_;
    float passTime_;
    Model* model_;
    Camera* camera_;
    Shader* shaderNormal_;
};

