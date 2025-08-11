#pragma once

#include <glad/glad.h>
#include <string>
#include <filesystem>

enum class ShaderType
{
    ShaderType_Vertex,
    ShaderType_Fragment
};

class ShaderStage
{
public:

    ShaderStage() = default;
    ShaderStage(const std::filesystem::path& shaderSourcePath, ShaderType shaderType);

    ShaderStage(const ShaderStage& other) = delete;
    ShaderStage& operator=(const ShaderStage& other) = delete;
    ShaderStage(ShaderStage&& other) noexcept;
    ShaderStage& operator=(ShaderStage&& other) noexcept;
    
    ~ShaderStage();

    bool Compile();

public:

    std::string GetShaderSourceString() const {return _shaderSource;}
    ShaderType GetShaderType() const {return _shaderType;}
    GLuint GetShaderObjectHandle() const { return _shaderObjectHandle; }
    
private:
    
    static std::string LoadSourceFromFile(const std::filesystem::path& shaderSourcePath);
    
private:

    std::string _shaderSource;
    ShaderType _shaderType;
    GLuint _shaderObjectHandle = 0;
    
};