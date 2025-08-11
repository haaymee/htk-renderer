#include "ShaderProgram.h"

#include <iostream>
#include "ShaderStage.h"

ShaderProgram::ShaderProgram()
    :_shaderProgramHandle(glCreateProgram())
{
}

ShaderProgram::ShaderProgram(const ShaderStage& vertShader, const ShaderStage& fragShader)
{
    if (vertShader.GetShaderType() == fragShader.GetShaderType())
        throw std::runtime_error("Cannot initialize Shader Program with duplicate Shader Stages");
    
    _shaderProgramHandle = glCreateProgram();
    AttachShaderStage(vertShader);
    AttachShaderStage(fragShader);
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept
{
    if (this != &other)
    {
        _shadersLinked = std::move(other._shadersLinked);
        _shaderProgramHandle = std::move(other._shaderProgramHandle);
        _isLinked = other._isLinked;
    }

    return *this;
}

ShaderProgram::~ShaderProgram()
{
    std::cout << "ShaderProgram gets Deleted";
    glDeleteProgram(_shaderProgramHandle);
}

void ShaderProgram::AttachShaderStage(const ShaderStage& shaderStage)
{
    if (_shadersLinked.contains(shaderStage.GetShaderType()))
        throw std::runtime_error(std::format("{} already linked", shaderStage.GetShaderFileName()));
    
    glAttachShader(_shaderProgramHandle, shaderStage.GetShaderObjectHandle());
    _shadersLinked.insert({shaderStage.GetShaderType(), shaderStage});
}

bool ShaderProgram::LinkProgram()
{
    if (_isLinked)
    {
        std::cout << "Shader Program has already been compiled\n";
        return false;
    }

    if (!AreAttachedShadersCompiled())
        return false;
    
    glLinkProgram(_shaderProgramHandle);

    GLint linkSuccess = GL_FALSE;
    glGetProgramiv(_shaderProgramHandle, GL_LINK_STATUS, &linkSuccess);

    if (!linkSuccess)
    {
        char infoLog[512];
        glGetProgramInfoLog(_shaderProgramHandle, sizeof(infoLog), nullptr, infoLog);
        throw std::runtime_error(std::format("Shader program linking failed: {}", infoLog));
    }

    _isLinked = true;
    return true;
}

bool ShaderProgram::AreAttachedShadersCompiled()
{
    for (const auto& [shaderType, shaderStage] : _shadersLinked)
        if (!shaderStage.HasAlreadyCompiled())
        {
            std::cout << std::format("Shader program cannot link: {} has not compiled\n",
                shaderStage.GetShaderFileName());
            return false;
        }

    return true;
}
