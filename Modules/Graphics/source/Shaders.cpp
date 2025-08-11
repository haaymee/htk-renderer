module;

#include <filesystem>

// #define EXCLUDE_TEMP_HEADER
#ifndef EXCLUDE_TEMP_HEADER
#include "Shaders.ixx"
#endif

module Graphics:Shaders;

ShaderStage::ShaderStage(const std::filesystem::path& shaderSourcePath, ShaderType shaderType)
    : _shaderType(shaderType)
{

}

ShaderStage::~ShaderStage()
{
    
}

bool ShaderStage::Compile()
{
    return false;
}

bool ShaderStage::LoadSourceFromFile(const std::filesystem::path& shaderSourcePath)
{
    return false;
}


