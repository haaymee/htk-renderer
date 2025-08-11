#pragma once

#include <unordered_map>
#include <glad/glad.h>

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
    
private:

    bool AreAttachedShadersCompiled();
    
private:

    std::unordered_map<ShaderType, const ShaderStage&> _shadersLinked = {};
    GLuint _shaderProgramHandle = 0;

    bool _isLinked = false;
};
