module;

#include <glad/glad.h>
#include <string>
#include <vector>
#include <filesystem>

export module Graphics:Shaders;

export enum class ShaderType
{
    ShaderType_Vertex,
    ShaderType_Fragment
};

export class ShaderStage
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

private:

    bool LoadSourceFromFile(const std::filesystem::path& shaderSourcePath);
    
private:

    std::string _shaderSource;
    ShaderType _shaderType;
    GLuint _shaderObjectHandle = 0;
    
};

export class ShaderProgram
{
    
};
