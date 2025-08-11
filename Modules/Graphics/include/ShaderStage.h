#pragma once

#include <glad/glad.h>
#include <string>
#include <filesystem>

enum class ShaderType
{
    ShaderType_Vertex,
    ShaderType_Fragment
};

///
/// Wrapper for individual shader objects before they get linked to a shader program.\n\n
/// They must be compiled manually before linking to a shader program.
///
class ShaderStage
{
public:

    ShaderStage() = default;
    ShaderStage(const std::filesystem::path& shaderSourcePath, ShaderType shaderType);

    ShaderStage(const ShaderStage& other) = delete;
    ShaderStage& operator=(const ShaderStage& other) = delete;
    // ShaderStage(ShaderStage&& other) noexcept;
    // ShaderStage& operator=(ShaderStage&& other) noexcept;
    
    ~ShaderStage();

    bool Compile();

public:

    std::string GetShaderSourceString() const {return _shaderSource;}
    std::string GetShaderFileName() const {return _shaderFileName;}
    ShaderType GetShaderType() const {return _shaderType;}
    GLuint GetShaderObjectHandle() const { return _shaderObjectHandle; }
    bool HasAlreadyCompiled() const {return _isCompiled;}
    
private:
    
    static std::string LoadSourceFromFile(const std::filesystem::path& shaderSourcePath);
    
private:

    std::string _shaderSource;
    std::string _shaderFileName;
    ShaderType _shaderType;
    GLuint _shaderObjectHandle = 0;
    
    bool _isCompiled = false;
    
};