#pragma once

#include <glad/glad.h>

#include "glm/fwd.hpp"

#include <format>
#include <iostream>
#include <string>
#include <unordered_map>

#include "glm/gtc/type_ptr.hpp"


enum class ShaderType;
class ShaderStage;

class ShaderProgram
{
public:

    ShaderProgram();
    ShaderProgram(const ShaderStage& vertShader, const ShaderStage& fragShader);
    ShaderProgram(const ShaderProgram& other) = delete;
    ShaderProgram(ShaderProgram&& other) = delete;
    
    ShaderProgram& operator=(ShaderProgram&& other) noexcept;
    ShaderProgram& operator=(const ShaderProgram&) = delete;

    ~ShaderProgram();
    
    void AttachShaderStage(const ShaderStage& shaderStage);
    bool LinkProgram();
    
    GLuint GetShaderProgramIdHandle() const {return _shaderProgramHandle;}
    bool HasAlreadyLinked() const {return _isLinked;}

public:

    template<typename T>
    void LinkUniform(const std::string& uniformName, const T& val)
    {
        GLint location = ValidateUniformLocation(uniformName);
        if (location == -1)
            return;

        if constexpr (std::is_same<T, float>()) // float uniforms
        {
            glProgramUniform1f(_shaderProgramHandle, location, val);
        }
        else if constexpr (std::is_same<T, glm::vec3>()) // vec3 uniforms
        {
            glProgramUniform3f(_shaderProgramHandle, location, val.x, val.y, val.z);
        }
        else if constexpr (std::is_same<T, glm::mat4>()) // matrix4x4 uniforms
        {
            glProgramUniformMatrix4fv(_shaderProgramHandle, location, 1, GL_FALSE, glm::value_ptr(val));
        }
        else
        {
            static_assert(std::_Always_false<T>, "Unsupported type");
        }
    }
    
private:

    bool AreAttachedShadersCompiled();

    GLint ValidateUniformLocation(const std::string& uniformName);
    
private:

    std::unordered_map<ShaderType, const ShaderStage&> _shadersLinked = {};
    GLuint _shaderProgramHandle = 0;

    bool _isLinked = false;
};
