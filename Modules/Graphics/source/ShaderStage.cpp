#include "ShaderStage.h"

#include <filesystem>
#include "FileHandling.h"

ShaderStage::ShaderStage(const std::filesystem::path& shaderSourcePath, ShaderType shaderType)
    : _shaderType(shaderType)
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
    glCompileShader(_shaderObjectHandle);
    
    GLint compileSuccess = GL_FALSE;
    glGetShaderiv(_shaderObjectHandle, GL_COMPILE_STATUS, &compileSuccess);
    
    return compileSuccess;
}

std::string ShaderStage::LoadSourceFromFile(const std::filesystem::path& shaderSourcePath)
{
    if (!FileHandling::DoesFileExist(shaderSourcePath))
        throw std::runtime_error("File does not exist");
    
    return FileHandling::ReadTextFileAsString(shaderSourcePath);
}


