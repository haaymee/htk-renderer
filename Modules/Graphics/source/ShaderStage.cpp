#include "ShaderStage.h"

#include <filesystem>
#include <iostream>

#include "FileHandling.h"

ShaderStage::ShaderStage(const std::filesystem::path& shaderSourcePath, ShaderType shaderType)
    : _shaderType(shaderType), _shaderFileName(shaderSourcePath.filename().string())
{
    _shaderSource = LoadSourceFromFile(shaderSourcePath);

    switch (_shaderType)
    {
    case ShaderType::ShaderType_Vertex:
        _shaderObjectHandle = glCreateShader(GL_VERTEX_SHADER);
        break;
    case ShaderType::ShaderType_Fragment:
        _shaderObjectHandle = glCreateShader(GL_FRAGMENT_SHADER);
        break;
    }
    
    const GLchar* src = _shaderSource.c_str();
    glShaderSource(_shaderObjectHandle, 1, &src, nullptr);
}

ShaderStage::~ShaderStage()
{
    
}

bool ShaderStage::Compile()
{
    if (_isCompiled)
    {
        std::cout << _shaderFileName << " has already been compiled\n";
        return false;
    }
    
    glCompileShader(_shaderObjectHandle);
    
    GLint compileSuccess = GL_FALSE;
    glGetShaderiv(_shaderObjectHandle, GL_COMPILE_STATUS, &compileSuccess);

    if (!compileSuccess)
    {
        char infoLog[512];
        glGetShaderInfoLog(_shaderObjectHandle, sizeof(infoLog), nullptr, infoLog);
        std::string errorMessage = std::format("{} shader compilation failed: {}", _shaderFileName, infoLog);

        std::cerr << errorMessage << "\n";
        throw std::runtime_error(errorMessage);
    }
    
    _isCompiled = true;
    return compileSuccess;
}

std::string ShaderStage::LoadSourceFromFile(const std::filesystem::path& shaderSourcePath)
{
    if (!FileHandling::DoesFileExist(shaderSourcePath))
        throw std::runtime_error("File does not exist");
    
    return FileHandling::ReadTextFileAsString(shaderSourcePath);
}


