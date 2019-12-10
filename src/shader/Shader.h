#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "GlUtil.h"

class Shader
{
private:
    unsigned int shaderProgram_;
    int shaderVertex_;
    int shaderFragment_;
    int shaderGeometry_;

public:
    Shader(const char* vertexShader, const char* fragmentShader, const char* geometryShader)
    {
        // 创建
        shaderVertex_ = GlUtil::GlCreateShader(GL_VERTEX_SHADER, vertexShader);
        shaderFragment_ = GlUtil::GlCreateShader(GL_FRAGMENT_SHADER, fragmentShader);
        if (geometryShader != nullptr)
        {
            shaderGeometry_ = GlUtil::GlCreateShader(GL_GEOMETRY_SHADER, geometryShader);
        }
        
        // 链接
        shaderProgram_ = glCreateProgram();
        GlUtil::GlLinkShaker(shaderProgram_, shaderVertex_, shaderFragment_, shaderGeometry_);
        
        // 链接以后可以删除了
        glDeleteShader(shaderVertex_);
        glDeleteShader(shaderFragment_);
        if(geometryShader != nullptr)
        {
            glDeleteShader(shaderGeometry_);
        }
    }

    unsigned int GetId() const { return shaderProgram_; }

    void use() 
    { 
        glUseProgram(shaderProgram_); 
    }

    // ------------------------------------------------------------------------
    void setBool(const std::string &name, bool value) const
    {         
        glUniform1i(glGetUniformLocation(shaderProgram_, name.c_str()), (int)value); 
    }
    // ------------------------------------------------------------------------
    void setInt(const std::string &name, int value) const
    { 
        glUniform1i(glGetUniformLocation(shaderProgram_, name.c_str()), value); 
    }
    // ------------------------------------------------------------------------
    void setFloat(const std::string &name, float value) const
    { 
        glUniform1f(glGetUniformLocation(shaderProgram_, name.c_str()), value); 
    }
    // ------------------------------------------------------------------------
    void setVec2(const std::string &name, const glm::vec2 &value) const
    { 
        glUniform2fv(glGetUniformLocation(shaderProgram_, name.c_str()), 1, &value[0]); 
    }
    void setVec2(const std::string &name, float x, float y) const
    { 
        glUniform2f(glGetUniformLocation(shaderProgram_, name.c_str()), x, y); 
    }
    // ------------------------------------------------------------------------
    void setVec3(const std::string &name, const glm::vec3 &value) const
    { 
        glUniform3fv(glGetUniformLocation(shaderProgram_, name.c_str()), 1, &value[0]); 
    }
    void setVec3(const std::string &name, float x, float y, float z) const
    { 
        glUniform3f(glGetUniformLocation(shaderProgram_, name.c_str()), x, y, z); 
    }
    // ------------------------------------------------------------------------
    void setVec4(const std::string &name, const glm::vec4 &value) const
    { 
        glUniform4fv(glGetUniformLocation(shaderProgram_, name.c_str()), 1, &value[0]); 
    }
    void setVec4(const std::string &name, float x, float y, float z, float w) 
    { 
        glUniform4f(glGetUniformLocation(shaderProgram_, name.c_str()), x, y, z, w); 
    }
    // ------------------------------------------------------------------------
    void setMat2(const std::string &name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(shaderProgram_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat3(const std::string &name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(shaderProgram_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(GLuint shader, std::string type)
    {
        GLint success;
        GLchar infoLog[1024];
        if(type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if(!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }
};

extern const GLchar* hello_triangle_vs;
extern const GLchar* hello_triangle_fs;
extern const GLchar* geometry_shader_vs;
extern const GLchar* geometry_shader_fs;
extern const GLchar* geometry_shader_gs;
extern const GLchar* geometry_shader_explode_vs;
extern const GLchar* geometry_shader_explode_fs;
extern const GLchar* geometry_shader_explode_gs;
extern const GLchar* geometry_shader_normal_vs;
extern const GLchar* geometry_shader_normal_fs;
extern const GLchar* geometry_shader_normal_gs;
extern const GLchar* geometry_shader_model_vs;
extern const GLchar* geometry_shader_model_fs;