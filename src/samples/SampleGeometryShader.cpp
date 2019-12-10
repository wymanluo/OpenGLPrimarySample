#include "SampleGeometryShader.h"
#include "shader/Shader.h"

#include <iostream>
#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include "shader/Shader.h"
#include "util/Camera.h"
#include "util/Model.h"
#include "util/Def.h"

enum EnumSampleType
{
    ENUM_SAMPLE_PRIMITIVE,            // 图元
    ENUM_SAMPLE_EXPLODE_MODEL,        // 爆炸
    ENUM_SAMPLE_NORMAL_VISIBLE_MODEL, // 向量可视化
};

SampleGeometryShader::SampleGeometryShader()
    : model_(nullptr)
    , camera_(nullptr)
    , passTime_(-1)
    , pause_(false)
    , type_(ENUM_SAMPLE_EXPLODE_MODEL)
{
    switch (type_)
    {
    case ENUM_SAMPLE_PRIMITIVE:
        InitShader(geometry_shader_vs, geometry_shader_fs, /*nullptr*/geometry_shader_gs);
        break;

    case ENUM_SAMPLE_EXPLODE_MODEL:
        InitShader(geometry_shader_explode_vs, geometry_shader_explode_fs, geometry_shader_explode_gs);
        break;

    case ENUM_SAMPLE_NORMAL_VISIBLE_MODEL:
        InitShader(geometry_shader_model_vs, geometry_shader_model_fs, nullptr);
        shaderNormal_ = new Shader(geometry_shader_normal_vs, geometry_shader_normal_fs, geometry_shader_normal_gs);
        break;

    default:
        break;
    };
}

SampleGeometryShader::~SampleGeometryShader()
{
    if (model_)
    {
        delete model_;
        model_ = nullptr;
    }
    if (camera_)
    {
        delete camera_;
        camera_ = nullptr;
    }
}

void SampleGeometryShader::Init()
{
    switch (type_)
    {
    case ENUM_SAMPLE_PRIMITIVE:
        InitVertex();
        break;

    case ENUM_SAMPLE_EXPLODE_MODEL:
        InitExpodeModel();
        break;

    case ENUM_SAMPLE_NORMAL_VISIBLE_MODEL:
        InitModel();
        break;

    default:
        break;
    };
}

void SampleGeometryShader::Draw()
{
    switch (type_)
    {
    case ENUM_SAMPLE_PRIMITIVE:
        DrawPrimitive();
        break;

    case ENUM_SAMPLE_EXPLODE_MODEL:
        DrawExpodeModel();
        break;

    case ENUM_SAMPLE_NORMAL_VISIBLE_MODEL:
        DrawModel();
        break;

    default:
        break;
    };
}

void SampleGeometryShader::OnKeyPress(int key, float delta)
{
    if (key == GLFW_KEY_UNKNOWN) return;

    switch (key)
    {
    case GLFW_KEY_W:
        {
            camera_->ProcessKeyboard(FORWARD, delta);
        }
        break;
    case GLFW_KEY_S:
        {
            camera_->ProcessKeyboard(BACKWARD, delta);
        }
        break;
    case GLFW_KEY_A:
        {
            camera_->ProcessKeyboard(LEFT, delta);
        }
        break;
    case GLFW_KEY_D:
        {
            camera_->ProcessKeyboard(RIGHT, delta);
        }
        break;
    case GLFW_KEY_P:
        {
            passTime_ = !pause_ ? glfwGetTime() : -1;
            pause_ = !pause_;
        }
        break;
    default:
        break;
    }
}

void SampleGeometryShader::InitVertex()
{
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,   
    };

    glGenVertexArrays(1, &VAO_);
    glBindVertexArray(VAO_);

    glGenBuffers(1, &VBO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void SampleGeometryShader::DrawPrimitive()
{
    __super::Draw();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawArrays(GL_POINTS, 0, 3);
}

void SampleGeometryShader::InitExpodeModel()
{
    model_ = new Model("F:/GitHub/OpenGLPrimarySample/res/nanosuit/nanosuit.obj");
    camera_ = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
}

float SampleGeometryShader::GetNormalScale() const
{
    const float time = pause_ ? passTime_ : glfwGetTime();
    const float normalScaleRange = 1.5f;
    return ((std::sin(time) + 1.0f) / 2) * normalScaleRange;
}

void SampleGeometryShader::DrawExpodeModel()
{
    Shader* shader = GetShader();
    if (!shader) return;

    glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)1280 / (float)880, 1.0f, 100.0f);
    glm::mat4 view = camera_->GetViewMatrix();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -1.15f, 0.0f));
    model = glm::scale(model, glm::vec3(0.155f, 0.155f, 0.155f));

    shader->use();
    shader->setMat4("model", model);
    shader->setMat4("view", view);
    shader->setMat4("projection", projection);
    shader->setFloat("normalScale", GetNormalScale());
    //shader->setFloat("time", glfwGetTime());
    //std::cout << "DrawExpodeModel: time, scale " << glfwGetTime() << "  " << GetNormalScale() << std::endl;
    model_->Draw(*shader);
}

void SampleGeometryShader::InitModel()
{
    model_ = new Model("F:/GitHub/OpenGLPrimarySample/res/nanosuit/nanosuit.obj");
    camera_ = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
}

void SampleGeometryShader::DrawModel()
{
    Shader* shader = GetShader();
    if (!shader) return;

    // 绘制模型
    glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)1280 / (float)880, 1.0f, 100.0f);
    glm::mat4 view = camera_->GetViewMatrix();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -1.15f, 0.0f));
    model = glm::scale(model, glm::vec3(0.155f, 0.155f, 0.155f));

    shader->use();
    shader->setMat4("model", model);
    shader->setMat4("view", view);
    shader->setMat4("projection", projection);
    model_->Draw(*shader);

    // 绘制法向量
    shaderNormal_->use();
    shaderNormal_->setMat4("projection", projection);
    shaderNormal_->setMat4("view", view);
    shaderNormal_->setMat4("model", model);
    model_->Draw(*shaderNormal_);
}

void SampleGeometryShader::OnMouseMove(double xpos, double ypos)
{
    static float lastX = (float)SCREEN_WIDTH / 2.0;
    static float lastY = (float)SCREEN_HEIGHT / 2.0;
    static bool firstMouse = true;
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    //camera_->ProcessMouseMovement(xoffset, yoffset);
}

void SampleGeometryShader::OnMouseScroll(double xoffset, double yoffset)
{
    if (camera_)
    {
        //camera_->ProcessMouseScroll(yoffset);
    }
}